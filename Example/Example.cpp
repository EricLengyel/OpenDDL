#include <windows.h>
#include "Example.h"


ExampleStructure::ExampleStructure() : Structure(kStructureExample)
{
	// An instance of the ExampleStructure class is constructed for each
	// occurrence of the "Example" structure in the OpenDDL file.
}

ExampleStructure::~ExampleStructure()
{
}

bool ExampleStructure::ValidateSubstructure(const DataDescription *dataDescription, const Structure *structure) const
{
	// In this example, we only allow the "float" data structure to be
	// contained inside an "Example" structure.

	return (structure->GetStructureType() == kDataFloat);
}


ExampleDataDescription::ExampleDataDescription()
{
}

ExampleDataDescription::~ExampleDataDescription()
{
}

Structure *ExampleDataDescription::CreateStructure(const String<>& identifier) const
{
	// This function is called for each structure identifier encountered
	// in an OpenDDL file. In this example, we only recognize the identifier
	// "Example", and if matched, we return a new instance of ExampleStructure.

	if (identifier == "Example")
	{
		return (new ExampleStructure);
	}

	return (nullptr);
}


int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR commandLine, int cmdShow)
{
	// Parse the file "Example.oddl".

	HANDLE handle = CreateFile("Example.oddl", GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (handle != INVALID_HANDLE_VALUE)
	{
		ExampleDataDescription	exampleDataDescription;
		DWORD					actual;

		// Allocate space for the entire file plus one more byte for the zero terminator.

		DWORD size = GetFileSize(handle, nullptr);
		char *buffer = new char[size + 1];

		// Read the entire contents of the file and put a zero terminator at the end.

		ReadFile(handle, buffer, size, &actual, nullptr);
		buffer[size] = 0;

		// Once the file is in memory, the DataDescription::ProcessText() function
		// is called to create the structure tree.

		DataResult result = exampleDataDescription.ProcessText(buffer);
		if (result == kDataOkay)
		{
			const Structure *structure = exampleDataDescription.GetRootStructure()->GetFirstSubnode();
			while (structure)
			{
				// This loops over all top-level structures in the file.

				// Do something with the data...

				structure = structure->GetNextSubnode();
			}
		}

		delete[] buffer;
	}

	return (0);
}
