#pragma once

#include "memory.h"

namespace bcstl
{
	template<typename T, uint64 _capacity>
	struct new_stack
	{
	private:
		T _data[_capacity];
		uint64 _size;
	public:
		typedef T value_type;
		typedef value_type* iterator;
	private:
		inline bool is_valid(uint64 index)
		{
			return index >= 0 && index <= _capacity;
		}
	public:
		new_stack()
		{
			clear();
		}

		~new_stack()
		{
			clear();
		}

		inline T& operator[](uint64 index)
		{
			return _data[index];
		}

		inline new_stack<T, _capacity>& operator=(const new_stack<T, _capacity>& src)
		{
			_size = src._size;
			for (uint64 i = 0; i < _size; i++)
			{
				_data[i] = src._data[i];
			}
			return *this;
		}

		inline T* get(uint64 index)
		{
			if (is_valid(index))
			{
				return _data[index];
			}
			return 0;
		}

		inline T* back()
		{
			return &_data[_size - 1];
		}

		inline T* begin()
		{
			return _data;
		}

		inline T* end()
		{
			return _data + _size;
		}

		inline T* data()
		{
			return _data;
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

		inline uint64 max_size() const
		{
			return 0x7FFFFFFF / (uint64)sizeof(T);
		}

		inline void push_back(T value)
		{
			if (_size < _capacity)
			{
				_data[_size] = value;
				_size++;
			}
		}

		inline void pop_back()
		{
			if (_size > 0)
			{
				_size--;
			}
		}

		inline void expand(uint64 value)
		{
			uint64 new_size = _size + value;
			resize(new_size);
		}

		inline void shrink(uint64 value)
		{
			uint64 new_size = _size - value;
			resize(new_size);
		}

		inline void resize(uint64 value)
		{
			if (is_valid(value))
			{
				_size = value;
			}
		}

		inline void clear()
		{
			BCSTL_MEMSET(this, 0, sizeof(*this));
		}
	};
}
