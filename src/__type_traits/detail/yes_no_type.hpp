#pragma once
namespace type_traits
{

	typedef char yes_type;
	struct no_type
	{
		char padding[8];
	};

} // namespace type_traits