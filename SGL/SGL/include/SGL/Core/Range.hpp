#ifndef RANGE_HPP
#define RANGE_HPP

#include <memory>
#include <initializer_list>
#include <SGL/Core\Types.hpp>

namespace sgl {
	template <typename T>
	class Range;

	template <typename T>
	class RangeIterator {
	private:
		uint32 _pos;
		const Range<T>* _p_vec;

	public:
		RangeIterator(const Range<T>* p_vec, uint32 pos);

		bool operator !=(const RangeIterator<T>& other) const {
			return _pos != other._pos;
		}

		T& operator *() const;

		const RangeIterator<T>& operator ++() {
			++_pos;

			return *this;
		}
	};

	template <typename T>
	RangeIterator<T>::RangeIterator(const Range<T>* p_vec, uint32 pos) : _pos(pos), _p_vec(p_vec) {

	}

	template <typename T>
	T& RangeIterator<T>::operator *() const {
		return _p_vec->ptr[_pos];
	}

	template <typename T>
	class Range {
	public:
		std::shared_ptr<T> ptr;
		const uint32 length;

		Range(std::initializer_list<T> liste);

		RangeIterator<T> begin() const {
			return RangeIterator<T>(this, 0);
		}

		RangeIterator<T> end() const {
			return RangeIterator<T>(this, this->length);
		}

		T& operator [](uint32 index) const {
			return this->ptr.get()[index];
		}
	};

	template <typename T>
	Range<T>::Range(std::initializer_list<T> liste) : length(liste.size()) {
		T* ptr = new T[this->length];

		uint32 i = 0;
		for (T val : liste) {
			ptr[i++] = static_cast<T>(val);
		}

		this->ptr = std::shared_ptr<T>(ptr);
	}
}

#endif