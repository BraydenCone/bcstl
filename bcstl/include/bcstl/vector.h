#pragma once

#include "bcstl/memory.h"

namespace bcstl
{
	template<typename T>
	struct vector
	{
	private:
		uint64 _size;
		uint64 _capacity;
		T* _data;

		inline uint64 expand_capacity(uint64 value) const
		{
			uint64 new_capacity = _capacity ? (_capacity + _capacity / 2) : 8;
			return new_capacity > value ? new_capacity : value;
		}
	public:
		inline vector()
		{
			_size = 0;
			_capacity = 0;
			_data = 0;
		}

		inline vector(uint64 size)
		{
			_size = 0;
			_capacity = 0;
			_data = 0;
			resize(size);
		}

		inline vector(const vector<T>& src)
		{
			_size = 0;
			_capacity = 0;
			_data = 0;
			operator=(src);
		}

		inline ~vector()
		{
			if (_data)
			{
				BCSTL_FREE(_data);
			}
		}

		inline vector<T>& operator=(const vector<T>& src)
		{
			clear();
			resize(src._size);
			if (src._data)
			{
				BCSTL_MEMCPY(_data, src._data, _size * sizeof(T));
			}
			return *this;
		}

		inline T& operator[](uint64 index)
		{
			return _data[index];
		}

		inline bool empty() const
		{
			return _size == 0;
		}

		inline uint64 size() const
		{
			return _size;
		}

		inline uint64 capacity() const
		{
			return _capacity;
		}

		inline T* data()
		{
			return _data;
		}

		inline void clear()
		{
			if (_data)
			{
				BCSTL_FREE(_data);
				_data = 0;
			}
			_size = 0;
			_capacity = 0;
		}

		inline void destruct()
		{
			for (uint64 i = 0; i < _size; ++i)
			{
				_data[i].~T();
			}
			clear();
		}

		inline void reserve(uint64 new_capacity)
		{
			if (new_capacity <= _capacity)
			{
				return;
			}
			T* new_data = (T*)BCSTL_ALLOC(new_capacity * sizeof(T));
			if (_data)
			{
				BCSTL_MEMCPY(new_data, _data, _size * sizeof(T));
				BCSTL_FREE(_data);
			}
			_data = new_data;
			_capacity = new_capacity;
		}

		inline void resize(uint64 value)
		{
			if (value > _capacity)
			{
				reserve(expand_capacity(value));
			}
			_size = value;
		}

		inline void shrink(uint64 new_size)
		{
			_size = new_size;
		}

		inline void push_back(const T& value)
		{
			if (_size == _capacity)
			{
				reserve(expand_capacity(_size + 1));
			}
			BCSTL_MEMCPY(&_data[_size], &value, sizeof(T));
			_size++;
		}

		inline void pop_back()
		{
			_size--;
		}

		inline void erase(uint64 index)
		{
			void* start_ptr = (void*)(&_data[index]);
			uint64 size = (_size - index) * sizeof(T);
			memmove(start_ptr, &_data[index + 1], size);
			_size--;
		}

		inline T& back()
		{
			return _data[_size - 1];
		}
	};
}
