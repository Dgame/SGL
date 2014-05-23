#ifndef RANGE_HPP
#define RANGE_HPP

#include <cstring>
#include <initializer_list>
#include <SGL/Core/Types.hpp>

namespace sgl {
	template <typename T>
	class Range;

	template <typename T>
	class RangeIterator final {
	private:
		uint32 _pos;
		const Range<T>* _p_vec;

	public:
		RangeIterator(const Range<T>* p_vec, uint32 pos);

		const RangeIterator<T>& operator ++() {
			++_pos;

			return *this;
		}

		T& operator *() const {
			return _p_vec->ptr[_pos];
		}
	};

	template <typename T>
	RangeIterator<T>::RangeIterator(const Range<T>* p_vec, uint32 pos) : _pos(pos), _p_vec(p_vec) {

	}

	template <typename T>
	bool operator ==(const RangeIterator<T>& lhs, const RangeIterator<T>& rhs ) {
		return lhs._p_vec == rhs._p_vec && lhs._pos == rhs._pos;
	}

	template <typename T>
	bool operator !=(const RangeIterator<T>& lhs, const RangeIterator<T>& rhs) {
		return !(lhs == rhs);
	}

	template <typename T>
	class Range {
	private:
		uint32 _length = 0;
		T* _ptr = nullptr;

	public:
		Range(std::initializer_list<T> liste);
		~Range();

		uint32 length() const {
			return _length;
		}

		const T* get() const {
			return _ptr;
		}

		RangeIterator<T> begin() const {
			return RangeIterator<T>(this, 0);
		}

		RangeIterator<T> end() const {
			return RangeIterator<T>(this, _length);
		}

		const T& operator [](uint32 index) const {
			return _ptr[index];
		}
	};

	template <typename T>
	Range<T>::Range(std::initializer_list<T> liste) : _length(liste.size()) {
		_ptr = new T[_length];
		std::memcpy(_ptr, liste.begin(), sizeof(T) * liste.size());
	}

	template <typename T>
	Range<T>::~Range() {
		delete[] _ptr;
	}
}

#endif