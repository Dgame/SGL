#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <initializer_list>
#include <SGL/Core\Types.hpp>

namespace sgl {
	template <typename T, uint32 N>
	struct Array;

	template <typename T, uint32 N>
	class Iterator {
	private:
		uint32 _pos;
		const Array<T, N>* _parr;

	public:
		Iterator(const Array<T, N>* parr, uint32 pos);

		bool operator !=(const Iterator<T, N>& other) const {
			return _pos != other._pos;
		}

		const T& operator *() const;

		const Iterator<T, N>& operator ++() {
			++_pos;

			return *this;
		}
	};

	template <typename T, uint32 N>
	Iterator<T, N>::Iterator(const Array<T, N>* parr, uint32 pos) : _pos(pos), _parr(parr) {

	}

	template <typename T, uint32 N>
	const T& Iterator<T, N>::operator *() const {
		return _parr->data[_pos];
	}

	template <typename T, uint32 N>
	struct Array {
		T data[N];

		Array() {

		}

		explicit Array(std::initializer_list<T> range);

		static Array<T, N> Fill(const T& val);
		void fill(const T& val);

		uint32 length() const {
			return N;
		}

		Iterator<T, N> begin() const {
			return Iterator<T, N>(this, 0);
		}

		Iterator<T, N> end() const {
			return Iterator<T, N>(this, N);
		}

		void operator =(std::initializer_list<T> range);

		T& operator [](uint32 index) {
			return this->data[index];
		}
	};

	template <typename T, uint32 N>
	Array<T, N>::Array(std::initializer_list<T> range) {
		const uint32 until = std::min(range.size(), N);

		uint32 i = 0;
		for (const T& val : range) {
			this->data[i++] = val;
			if (i >= until)
				break;
		}
	}

	template <typename T, uint32 N>
	void Array<T, N>::operator =(std::initializer_list<T> range) {
		const uint32 until = std::min(range.size(), N);

		uint32 i = 0;
		for (const T& val : range) {
			this->data[i++] = val;
			if (i >= until)
				break;
		}
	}

	template <typename T, uint32 N>
	Array<T, N> Array<T, N>::Fill(const T& val) {
		Array<T, N> arr;
		arr.fill(val);

		return std::move(arr);
	}

	template <typename T, uint32 N>
	void Array<T, N>::fill(const T& val) {
		for (T& item : data) {
			item = val;
		}
	}
}

#endif