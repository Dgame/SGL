#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <initializer_list>
#include <SGL/Core\Types.hpp>

namespace sgl {
	template <typename T, uint32 N>
	struct Array;

	template <typename T, uint32 N>
	class ArrayIterator final {
	private:
		uint32 _pos;
		const Array<T, N>* _parr;

	public:
		ArrayIterator(const Array<T, N>* parr, uint32 pos);

		bool operator !=(const ArrayIterator<T, N>& other) const {
			return _pos != other._pos;
		}

		const T& operator *() const;

		const ArrayIterator<T, N>& operator ++() {
			++_pos;

			return *this;
		}
	};

	template <typename T, uint32 N>
	ArrayIterator<T, N>::ArrayIterator(const Array<T, N>* parr, uint32 pos) : _pos(pos), _parr(parr) {

	}

	template <typename T, uint32 N>
	const T& ArrayIterator<T, N>::operator *() const {
		return _parr->data[_pos];
	}

	template <typename T, uint32 N>
	struct Array final {
		T data[N];

		explicit Array() {

		}

		explicit Array(std::initializer_list<T> range);

		uint32 length() const {
			return N;
		}

		ArrayIterator<T, N> begin() const {
			return ArrayIterator<T, N>(this, 0);
		}

		ArrayIterator<T, N> end() const {
			return ArrayIterator<T, N>(this, N);
		}

		void operator =(std::initializer_list<T> range);

		T& operator [](uint32 index) {
			return this->data[index];
		}

		const T& at(uint32 index) const {
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
}

#endif