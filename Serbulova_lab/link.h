#pragma once

struct link
{
	int csInID;
	int csOutID;
	int pipeID;

	friend bool operator<(const link& left, const link& right) noexcept //добавили компаратор(?) который позволит нам использовать set<link>
	{
		return std::tie(left.csInID, left.csOutID, left.pipeID) < std::tie(right.csInID, right.csOutID, right.pipeID);
	}



};

