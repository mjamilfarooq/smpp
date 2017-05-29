/*
 * thread_pool.h
 *
 *  Created on: Apr 20, 2017
 *      Author: jamil
 */

#ifndef UTILS_THREAD_POOL_THREAD_POOL_H_
#define UTILS_THREAD_POOL_THREAD_POOL_H_



#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>
#include <algorithm>
#include <chrono>

#include "async_queue.h"

namespace utils {



		template<class T>
		class thread_pool {
			std::mutex _mt;
			std::condition_variable _cv;

			class worker: public std::thread {
				bool stop;
				async_queue<T> const & pending_tasks; //worker will share pending tasks lists
			public:
				worker(async_queue<T> & pending_tasks):
					std::thread(&worker::do_work, this),
					pending_tasks(pending_tasks),
					stop(false) {

				}

				void stop_work() {
					stop = true;
				}

			private:

				void do_work() {
					while(!stop) {
						std::cout<<"thread id "<<std::this_thread::get_id()<<std::endl;
						std::lock_guard<std::mutex> lock(_mt);
						auto task = pending_tasks.front();
						pending_tasks.pop();
						task();		//execute task

						std::this_thread::sleep_for(std::chrono::seconds(1));
					}

				}

			};


			using pool_type = typename std::vector<worker>;
			async_queue<T> pending_tasks;
			pool_type pool;
			size_t size;

			std::atomic_bool stop;

		public:
			thread_pool(size_t size):
				size(size),
				pool(size),
				stop(false) {

				//initialize worker threads
				std::for_each(pool.begin(), pool.end(), [this](pool_type::reference th){
					th = std::thread(&thread_pool::loop, this);
					th.detach();
				});
			}




			void set_max_threads(size_t size) {
				if ( size == this->size ) return;

				if ( size > this->size ) {
					//increase worker threads
					add_workers(size-this->size);
				} else {
					//reduce workers thread
					delete_workers( this->size - size );
				}
			}


			size_t get_max_threads() {
				return size;
			}

			size_t get_num_threads() {
				return size;
			}

			size_t unprocessed() {
				return size;
			}

			void set_max_unused_threads(size_t size) {
				 this->size = size;
			}

			size_t get_max_unused_threads() {
				return size;
			}






			void push(T task) {
				pending_tasks.push(task);
			}

			void free() {
				stop = true;
				pending_tasks.clear();	//free pending tasks


			}

		private:

			void add_workers(size_t size) {
				for ( auto i = 0; i < size; i++ ) {
					auto th = std::thread(&thread_pool::loop, this);
					pool.emplace_back(th);
					th.detach();
				}
			}

			void delete_workers(size_t size) {
				std::for_each (pool.rbegin(), pool.rend(), [] (pool_type::reference th) {
					th.exit();
				});
			}

		};

}




#endif /* UTILS_THREAD_POOL_THREAD_POOL_H_ */
