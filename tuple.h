#pragma once

#include <cstddef>
#include <utility>



namespace __whoAmIFk_tuple {
	template<std::size_t index,typename T>
	class _tuple_impl
	{
	public:
		typedef T const& const_ref;
		typedef T&& move_type;
		typedef T& ref;
		typedef T val_type;
		_tuple_impl(const_ref v)
		{
			_val = v;
		}

		_tuple_impl(move_type v)
		{
			_val = std::move(v);
		}

		ref get()
		{
			return _val;
		}
	private:
		val_type _val;
	};


	template<std::size_t index, typename... types>
	class _tuple_recurr_base
	{

	};

	template<std::size_t index, typename L, typename... types>
	class _tuple_recurr_base :
		public _tuple_impl < index, typename std::remove_reference<L>::type>,
		public _tuple_recurr_base<index + 1, types...>
	{
	public:
		template<typename CL, typename... CArgs>
		_tuple_recurr_base(CL&& arg,CArgs&&... args)
			: _tuple_impl<index, typename std::remove_reference<CL>::type>
			(std::forward<CL>(arg)),
			_tuple_recurr_base<index + 1, types...>(std::forward<CArgs>(args)...)
		{

		}
	};


	template<typename L, typename... types>
	class tuple : public _tuple_recurr_base<0, L, types...>
	{
		template<typename... CArgs>
		tuple(CArgs&&... args) :
			_tuple_recurr_base<0, L, types...>(std::forward<CArgs>(args)...)
		{

		}

		template<typename... Args>
		friend bool operator==(tuple<Args...>& t1, tuple<Args...>& t2);
	};

	// not finished

	template<std::size_t index, typename L, typename... Args>
	struct _extract_type_at
	{
		using type = typename _extract_type_at<index - 1, Args..>::type;
	};

	template<typename L, typename... Args>
	struct _extract_type_at<0, L, Args...>
	{
		using type = L;
	};

	template<std::size_t index, typename... Args>
	auto& get(tuple<Args...>& t)
	{
		return(static_cast<_tuple_impl<index, typename _extract_type_at<index, Args...>::type>&>(t)).get();
	}

	template<std::size_t index, typename... Args>
	bool compare_tuple(tuple<Args...>& t1, tuple<Args...>& t2)
	{
		if constexpr (index == 0)
		{
			return get<0>(t1) == get<0>(t2);
		}
		else
		{
			return get<index>(t1) == get<index>(t2)
				&& compare_tuple<index - 1>(t1, t2);
		}
	}
	
	template<typename... Args>
	bool operator==(tuple<Args...>& t1, tuple<Args...>& t2)
	{
		return compare_tuple<sizeof...(Args) - 1>(t1, t2);
	}


};