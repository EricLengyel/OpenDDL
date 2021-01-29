#ifndef Example_h
#define Example_h


#include "TSOpenDDL.h"


using namespace Terathon;


/*
	This is the simplest example of what needs to be done in order to read an
	OpenDDL file that follows a specific format. In this example, a single type
	of structure is recognized, and its identifier is "Example".
*/


enum
{
	kStructureExample	= 'EXPL'		// The 32-bit type of the "Example" structure.
};


/*
	The following class represents each "Example" structure in the file.
*/

class ExampleStructure : public Structure
{
	public:

		ExampleStructure();
		~ExampleStructure();

		bool ValidateSubstructure(const DataDescription *dataDescription, const Structure *structure) const override;
};


/*
	The following class represents the entire OpenDDL file.
*/

class ExampleDataDescription : public DataDescription
{
	public:

		ExampleDataDescription();
		~ExampleDataDescription();

		Structure *CreateStructure(const String<>& identifier) const override;
};


#endif
