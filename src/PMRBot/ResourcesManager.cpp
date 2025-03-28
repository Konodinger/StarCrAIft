#include "ResourcesManager.h"
#include <BWAPI.h>
#include <algorithm>

int ResourcesManager::getResourceLeft(ResourceType type) {
	int left = m_resources[(int)type];
	for (const auto& loan : m_loans) {
		if (loan.resourceType == type) {
			left -= loan.amount;
		}
	}

	return std::max(0, left);
}

void ResourcesManager::updateResources() {
	m_resources[(int)ResourceType::MINERALS] = BWAPI::Broodwar->self()->minerals();
	m_resources[(int)ResourceType::GAS] = BWAPI::Broodwar->self()->gas();
	m_resources[(int)ResourceType::SUPPLY] = BWAPI::Broodwar->self()->supplyUsed();
	m_resources[(int)ResourceType::SUPPLY_TOTAL] = BWAPI::Broodwar->self()->supplyTotal();
}

void ResourcesManager::allocate_resource(ResourceType resourceType, int amount, void* borrower) {
	m_loans.push_back({ resourceType, amount, borrower });
}

void ResourcesManager::free_resource(void* borrower) {
	m_loans.erase(std::remove_if(m_loans.begin(), m_loans.end(), [borrower](const Loan& loan) {
		return loan.borrower == borrower;
		}), m_loans.end());
}

// Borrower can only borrow if first in line
bool ResourcesManager::can_borrow(void* borrower) {
	if (m_loans.empty()) return false; // Didn't borrow anything
	if (m_loans.front().borrower == borrower) {
		return m_resources[(int) m_loans.front().resourceType] >= m_loans.front().amount;
	}
	return false;
}

void ResourcesManager::drawDebugInformation() {
	// Draw a table with the resources
	BWAPI::Broodwar->drawTextScreen(20, 0, "Resources (free / total)");
	BWAPI::Broodwar->drawTextScreen(20, 20, "Minerals: %d / %d", getResourceLeft(ResourceType::MINERALS), getResource(ResourceType::MINERALS));
	BWAPI::Broodwar->drawTextScreen(20, 40, "Gas: %d / %d", getResourceLeft(ResourceType::GAS), getResource(ResourceType::GAS));
	BWAPI::Broodwar->drawTextScreen(20, 60, "Supply: %d / %d (max: %d)", getResourceLeft(ResourceType::SUPPLY), getResource(ResourceType::SUPPLY), getResource(ResourceType::SUPPLY_TOTAL));

}
