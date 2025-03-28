#pragma once
#include <vector>

enum class ResourceType {
	MINERALS,
	GAS,
	SUPPLY,
	SUPPLY_TOTAL
};

struct Loan {
	ResourceType resourceType;
	int amount;
	void* borrower;
};


/*
* Makes sure the resources are allocated to the most urgent matters, and that no process is uselessly hoarding them.
*/
class ResourcesManager {

public:
	ResourcesManager() { m_resources.resize(4); }
	// Resources
	inline int getResource(ResourceType type) { return m_resources[(int)type]; }
	int getResourceLeft(ResourceType type);
	void updateResources();
	// Loans
	void allocate_resource(ResourceType resourceType, int amount, void* borrower);
	void free_resource(void* borrower);
	bool can_borrow(void* borrower);

	void drawDebugInformation();

private:
	// Resources
	std::vector<int> m_resources;

	// Loans
	std::vector<Loan> m_loans;
};

