//
// vcruntime_exception.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// <exception> functionality that is implemented in the VCRuntime.
//
#pragma once

#include <eh.h>

#ifdef _M_CEE_PURE
    #include <vcruntime_new.h>
#endif

#pragma pack(push, _CRT_PACKING)
#if !defined RC_INVOKED && _HAS_EXCEPTIONS

_CRT_BEGIN_C_HEADER

struct __std_exception_data
{
    char const* _What;
	int        _DoFree;
};

_VCRTIMP void __cdecl __std_exception_copy(
    _In_  __std_exception_data const* _From,
    _Out_ __std_exception_data*       _To
    );

_VCRTIMP void __cdecl __std_exception_destroy(
    _Inout_ __std_exception_data* _Data
    );

_CRT_END_C_HEADER



class exception
{
public:

	exception() throw();

	explicit exception(char const* const& _Message) throw();

	exception(char const* const& _Message, int) throw()
#ifndef _ATL_XP_TARGETING
		;
#else
		:_Data{ _Message,0 }
	{

	}
#endif

	exception(exception const& _Other) throw();

	exception& operator=(exception const& _Other) throw();

	virtual ~exception() throw();

	virtual char const* what() const;

private:

    __std_exception_data _Data;
};

namespace std {

using ::exception;

class bad_exception
    : public exception
{
public:

    bad_exception() throw()
        : exception("bad exception", 1)
    {
    }
};

class bad_alloc
    : public exception
{
public:

    bad_alloc() throw()
        : exception("bad allocation", 1)
    {
    }

private:

    friend class bad_array_new_length;

    bad_alloc(char const* const _Message) throw()
        : exception(_Message, 1)
    {
    }
};

class bad_array_new_length
    : public bad_alloc
{
public:

    bad_array_new_length() throw()
        : bad_alloc("bad array new length")
    {
    }
};

} // namespace std

#endif // !RC_INVOKED && _HAS_EXCEPTIONS
#pragma pack(pop)

/*
 * Copyright (c) 1992-2012 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
  V6.00:0009 */
