// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DEMOLITION_API ConstID
{
public:
	ConstID(const int _Id);
	~ConstID(){};

public:
	bool operator==(ConstID A) {
		return Id == A.Id;
	};

	int operator()() const {
		return Id;
	};

	bool operator==(ConstID A) const {
		return Id == A.Id;
	};

public:
	const int Id;
	static const ConstID INVALID_ID;
};

inline int GetTypeHash(const ConstID A)
{
	return (int)A();
}
