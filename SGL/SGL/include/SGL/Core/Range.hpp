#ifndef RANGE_HPP
#define RANGE_HPP

#include <memory>
#include <initializer_list>
#include <SGL/Core\Types.hpp>

namespace sgl {
	template <typename T>
	class Range;

	template <typename T>
	class Iterator {
	private:
		uint32 _pos;
		const Range<T>* _p_vec;

	public:
		Iterator(const Range<T>* p_vec, uint32 pos);

		bool operator !=(const Iterator<T>& other) const {
			return _pos != other._pos;
		}

		T& operator *() const;

		const Iterator<T>& operator ++() {
			++_pos;

			return *this;
		}
	};

	template <typename T>
	Iterator<T>::Iterator(const Range<T>* p_vec, uint32 pos) : _pos(pos), _p_vec(p_vec) {

	}

	template <typename T>
	T& Iterator<T>::operator *() const {
		return _p_vec->ptr[_pos];
	}

	template <typename T>
	class Range {
	public:
		std::shared_ptr<T> ptr;
		const uint32 length;

		Range(std::initializer_list<T> liste);

		Iterator<T> begin() const {
			return Iterator<T>(this, 0);
		}

		Iterator<T> end() const {
			return Iterator<T>(this, this->length);
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