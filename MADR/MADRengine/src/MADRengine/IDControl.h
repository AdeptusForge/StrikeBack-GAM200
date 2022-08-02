#pragma once
#include "MADRpch.h"

//Defines for the total id sizes for various ID controllers.
#define TOTAL_COMPONENT_ID 16384
//#define TOTAL_INVENTORY_ID 512
//#define TOTAL_CAMERA_ID 32
//#define TOTAL_MAPENTITY_ID 32

//Class for storing, creating, deleting, finding, and recycling old id's
class IDController
{
private:
	unsigned int IDCheck;
	std::vector <unsigned int> recycledIDs;
	//DO NOT EDIT DURING RUNTIME
	unsigned int totalIDsAvailable;
	unsigned int GetFirstAvailableID() {
		if (recycledIDs.size() >= 1)
		{
			//WriteDebug("Using recycled ID");
			unsigned int result = *std::min_element(recycledIDs.begin(), recycledIDs.end());
			recycledIDs.erase(std::min_element(recycledIDs.begin(), recycledIDs.end()));
			return result;
		}
		else
		{
			unsigned int newID = IDCheck;
			IDCheck++;
			return newID;
		}
	};
public:
	unsigned int GetTotalAvailable() { return totalIDsAvailable; }
	std::vector<unsigned int>* GetRecycledIDs() { return &recycledIDs; }

	//IDController constructor.
	//Takes in max number of ids for said controller.
	IDController(unsigned int maxIDs) :
		IDCheck(0), totalIDsAvailable(maxIDs) {};

	//Class that holds ID information and is manipulated and stored 
	//within an IDController
	class MADR_ID
	{
	private:
		//ID
		unsigned int id;
		//Pointer to the code structure the ID is attached to
		const void* ptr; 

	public:
		const unsigned int ID() { return id; }
		//DO NOT USE. USE 'CreateNewID()' UNDER AN 'IDController' INSTEAD.
		//OTHERWISE, THIS WILL BREAK THE ID SCHEMA.
		MADR_ID(unsigned int ID, const void *p) : id(ID), ptr(p) {};

	};

private:
	std::vector <MADR_ID> allIDs;
	//Finds an ID via its ID number
	struct IDFinder {

		IDFinder(unsigned int const& id) : ID(id) { }
		bool operator () (MADR_ID el) const { return  el.ID() == ID; }
	private:
		unsigned int ID;
	};

public:
	std::vector<MADR_ID>* GetAllIDs() { return &allIDs; }
	//Creates a pointer to a new ID. Use a positive number to create an ID with a specific number. 
	//Negative numbers are used for standard generation
	MADR_ID* CreateNewID(const void *p, const int setID = -1)
	{
		if (allIDs.size() >= totalIDsAvailable)
		{
			//WriteDebug("ERROR -- TOO MANY IDS CREATED");
			return nullptr;
		}

		if (setID < 0)
		{
			allIDs.push_back(MADR_ID(GetFirstAvailableID(), p));
		}
		else
		{
			if (std::none_of(allIDs.begin(), allIDs.end(), [=](MADR_ID elem) {return setID == elem.ID(); }))
			{
				allIDs.push_back(MADR_ID(setID, p));
			}
			else
			{
				//WriteDebug("Cannot Create Identical ID");
			}
		}
		return &allIDs.back();
	};

	void DeleteID(MADR_ID* idCheck)
	{
		std::vector<MADR_ID>::iterator eraser = std::find_if(allIDs.begin(), allIDs.end(), [&](MADR_ID i) {return i.ID() == idCheck->ID(); });
		allIDs.erase(eraser);
	}
	void DeleteID(unsigned int idCheck)
	{
		std::vector<MADR_ID>::iterator eraser = std::find_if(allIDs.begin(), allIDs.end(), [&](MADR_ID i) {return i.ID() == idCheck; });
		allIDs.erase(eraser);
	}

	void RecycleID(MADR_ID* idCheck)
	{
		if (!std::none_of(recycledIDs.begin(), recycledIDs.end(), [&](unsigned int i) {return i == idCheck->ID(); })) 
		{
			//WriteDebug("ERROR -- Cannot recycle already recycled ID.");
		}
		else
		{
			DeleteID(idCheck);
			recycledIDs.push_back(idCheck->ID());
		}
	}
};

void IDStartup();
IDController* GetIDController(std::string purpose);