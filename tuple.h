#pragma once

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

	};


	template<typename L, typename... types>
	class tuple : public _tuple_recurr_base<0, L, types...>
	{

	};
};