#pragma once

#ifndef __UNCOPYABLE_HPP_INCLUDED__
#define __UNCOPYABLE_HPP_INCLUDED__ 

class NoncopyableCopy abstract
{
private:
	NoncopyableCopy(CONST NoncopyableCopy&);

	NoncopyableCopy& operator=(CONST NoncopyableCopy&);

public:
	explicit NoncopyableCopy() { };
	virtual ~NoncopyableCopy() { };
};

class NoncopyableMove abstract
{
private:
	NoncopyableMove(NoncopyableMove&&);

	NoncopyableMove& operator=(NoncopyableMove&&);

public:
	explicit NoncopyableMove() { };
	virtual ~NoncopyableMove() { };
};

class NoncopyableFull abstract : public NoncopyableCopy, public NoncopyableMove
{
public:
	explicit NoncopyableFull() :
		NoncopyableCopy(),
		NoncopyableMove()
	{ };

	virtual ~NoncopyableFull() { };
};

#endif // __UNCOPYABLE_HPP_INCLUDED__

