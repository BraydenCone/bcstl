#pragma once

#include "bcstl/memory.h"
#include "bcstl/stack.h"
#include "bcstl/crypto.h"

namespace bcstl
{
	// struct forward declarations
	template<typename T>
	struct string_base;
	template<typename T, uint64 _capacity>
	struct fixed_string_base;

	// using forward declaration
	template<uint32 _capacity>
	using fixed_string = fixed_string_base<char, _capacity>;
	template<uint32 _capacity>
	using w_fixed_string = fixed_string_base<wchar_t, _capacity>;

	// typedef forward declarations
	typedef string_base<char> string;
	typedef string_base<wchar_t> w_string;
	typedef fixed_string<21> integer_fixed_string;

	// functions forward declarations
	template<typename T>
	inline uint64 get_length(const T* src);
	template<typename T>
	inline bool hash_compare(T* src_1, T* src_2, uint64 size_1, uint64 size_2);
	inline bool string_compare(const char* str_1, const char* str_2);
	inline bool w_string_compare(const wchar_t* str_1, const wchar_t* str_2);

	template<typename T>
	struct string_base
	{
	private:
		T* _data;
		uint64 _size, _capacity;
	public:
		inline string_base()
		{
			BCSTL_MEMSET(this, 0, sizeof(*this));
		}

		inline string_base(const T* src, uint64 length = 0)
		{
			BCSTL_MEMSET(this, 0, sizeof(*this));
			set(src, length);
		}

		inline ~string_base()
		{
			clear();
		}

		inline string_base<T>& operator=(const T* src)
		{
			set(src, 0);
			return *this;
		}

		inline T& operator[](uint64 index)
		{
			return _data[index];
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

		inline void set(const T* src, uint64 length = 0)
		{
			if (length == 0)
			{
				length = get_length<T>(src);
			}
			if (length > _size)
			{
				_size = length;
				_capacity = _size + 1;
				if (_data)
				{
					BCSTL_FREE(_data);
				}
				_data = (T*)BCSTL_ALLOC(_capacity * sizeof(T));
			}
			BCSTL_MEMCPY(_data, src, _size);
			_data[_size] = 0;
		}

		inline bool empty()
		{
			return (bool)(_size == 0);
		}

		inline uint64 size()
		{
			return _size;
		}

		inline const uint64 capacity()
		{
			return _capacity;
		}

		inline T* c_str()
		{
			return _data;
		}

		bool compare(const string_base& str)
		{
			return hash_compare<T>(_data, str._data, _size * sizeof(T), str._size * sizeof(T));
		}

		bool compare(const T& str)
		{
			return hash_compare<T>(_data, str, _size * sizeof(T), get_length<T>(str) * sizeof(T));
		}
	};

	template<typename T, uint64 _capacity>
	struct fixed_string_base
	{
	private:
		uint64 _size;
		new_stack<T, _capacity> _stack;
	public:
		inline fixed_string_base()
		{
			_size = 0;
		}

		inline fixed_string_base(const T* src, uint64 length = 0)
		{
			set(src, length);
		}

		inline fixed_string_base<T, _capacity>& operator=(const T* src)
		{
			set(src);
			return *this;
		}

		inline T& operator[](uint64 index)
		{
			return _stack[index];
		}

		inline void set(const T* src, uint64 length = 0)
		{
			if (length == 0) { length = get_length<T>(src); }
			if (length > _capacity) { length = _capacity; }
			_size = length;
			BCSTL_MEMCPY(_stack.data(), src, length);
		}

		inline bool empty()
		{
			return (bool)(_size == 0);
		}

		inline uint64 size()
		{
			return _size;
		}

		inline const uint64 capacity()
		{
			return _capacity;
		}

		inline const uint64 size_in_bytes()
		{
			return _capacity * sizeof(T);
		}

		inline T* data()
		{
			return _stack.data();
		}

		bool compare(const T& str)
		{
			return hash_compare<T>(_stack.data(), str, _size * sizeof(T), get_length<T>(str) * sizeof(T));
		}
	};

	template<typename T>
	inline uint64 get_length(const T* src)
	{
		uint64 len = 0;
		while (*src) { src++; len++; }
		return len;
	}

	template<typename T>
	inline bool hash_compare(T* src_1, T* src_2, uint64 size_1, uint64 size_2)
	{
		if (size_1 == size_2)
		{
			uint32 hash_1 = murmur::hash(src_1, size_1, 0);
			uint32 hash_2 = murmur::hash(src_2, size_2, 0);
			return (bool)(hash_1 == hash_2);
		}
		return 0;
	}

	template<typename T>
	inline bool string_compare_base(T* str_1, T* str_2)
	{
		return hash_compare<T>(str_1, str_2, get_length<T>(str_1) * sizeof(T), get_length<T>(str_2) * sizeof(T));
	}

	inline bool string_compare(const char* str_1, const char* str_2)
	{
		return string_compare_base<const char>(str_1, str_2);
	}

	inline bool w_string_compare(const wchar_t* str_1, const wchar_t* str_2)
	{
		return string_compare_base<const wchar_t>(str_1, str_2);
	}

	inline wchar_t to_wchar(char c)
	{
		char wide_char[2] = { 0, c };
		return (wchar_t)wide_char;
	}
}
