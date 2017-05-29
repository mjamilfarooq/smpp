/*
 * async_queue.h
 *
 *  Created on: Apr 20, 2017
 *      Author: jamil
 */

#ifndef UTILS_THREAD_POOL_ASYNC_LIST_H_
#define UTILS_THREAD_POOL_ASYNC_LIST_H_


#include <queue>
#include <mutex>

using namespace std;

namespace utils {
	template <typename T>
	class async_queue: public list<T> {
		mutex _mt;
	public:

		using value_type = typename list<T>::value_type;
		using reference = typename list<T>::reference;
		using const_reference = typename list<T>::const_reference;
		using size_type = typename list<T>::size_type;

		reference front() {
			lock_guard<mutex> lock(_mt);
			return queue<T>::front();
		}

		const_reference front() const {
			lock_guard<mutex> lock(_mt);
			return queue<T>::front();
		}

		reference back() {
			lock_guard<mutex> lock(_mt);
			return queue<T>::back();
		}

		const_reference back() const {
			lock_guard<mutex> lock(_mt);
			return queue<T>::back();
		}

		bool empty() const {
			lock_guard<mutex> lock(_mt);
			return queue<T>::empty();
		}

		size_type size() const {
			lock_guard<mutex> lock(_mt);
			return queue<T>::size();
		}

		void push(const value_type& value) {
			lock_guard<mutex> lock(_mt);
			queue<T>::push(value);
		}

		void push(value_type&& value) {
			lock_guard<mutex> lock(_mt);
			queue<T>::push(std::move(value));
		}

		template <class ...Args>
		void emplace(Args ...args) {
			lock_guard<mutex> lock(_mt);
			queue<T>::emplace(std::forward<Args>(args)...);
		}

		template <class ...Args>
		reference emplace(Args ...args) {
			lock_guard<mutex> lock(_mt);
			return queue<T>::emplace(std::forward<Args>(args)...);
		}


		void pop() {
			lock_guard<mutex> lock(_mt);
			queue<T>::pop();
		}


		void swap(async_queue& other) {
			lock_guard<mutex> lock(_mt);
			queue<T>::swap(other);
		}

	};
}


#endif /* UTILS_THREAD_POOL_ASYNC_LIST_H_ */
