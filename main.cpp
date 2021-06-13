#include "BST.hpp"
#include "Node.hpp"
#include "TreePrinter.hpp"
#include <iostream>
#include <vector>

short menu();
void performAction(short choice, BST *bst, int key = 0, int key2 = 0);

int main(int argc, char* argv[]) {
	BST* bst = new BST;

	short choice = menu();
	while (choice != 0) {
		switch (choice) {
			case 1:
			case 2: {
				std::cout << "Enter key: ";

				int key;
				std::cin >> key;

				std::cout << std::endl;

				performAction(choice, bst, key);

				break;
			}
			case 3: {
				performAction(choice, bst);

				break;
			}
			case 4:
			case 5: {
				performAction(choice, bst);

				break;
			}
			case 6: {
				int key, key2;
				std::cout << "Enter the first value: ";
				std::cin >> key;
				std::cout << std::endl << "Enter the second value: ";
				std::cin >> key2;

				performAction(choice, bst, key, key2);

			}
		}

		choice = menu();
	}

	return 0;
}

short menu() {
	short choice = 99;

	std::cout << "Select:" << std::endl;
	std::cout << "1. Insert new node" << std::endl;
	std::cout << "2. Delete existing node" << std::endl;
	std::cout << "3. Print tree" << std::endl;
	std::cout << "4. Find minimum value" << std::endl;
	std::cout << "5. Find maximum value" << std::endl;
	std::cout << "6. Find values in a range" << std::endl;
	std::cout << "0. Exit" << std::endl;

	std::cout << "Choice: ";
	std::cin >> choice;
	std::cout << std::endl;

	return choice;
}

void performAction(short choice, BST* bst, int key, int key2) {
	switch (choice) {
		case 1: {
			bst->insert(bst->getRoot(), key);
			break;
		}
		case 2: {
			bst->deleteNode(bst->getRoot(), key);
			break;
		}
		case 3: {
			std::cout << std::endl;
			bst->reconstruct(bst->getRoot());
			TreePrinter printer(bst);
			printer.print();
			break;
		}
		case 4: {
			Node *min = bst->Find_Min(bst->getRoot());
			
			if (min != nullptr) {
				std::cout << "Minimum value: " << min->getKey() << std::endl;
			}

			break;
		}
		case 5: {
			Node* max = bst->Find_Max(bst->getRoot());

			if (max != nullptr) {
				std::cout << "Maximum value: " << max->getKey() << std::endl;
			}

			break;
		}
		case 6: {
			std::vector<Node *> values = bst->Find_Between(bst->getRoot(), key, key2);

			std::cout << "Values between " << key << " and " << key2 << std::endl;
			for (auto& node : values) {
				std::cout << node->getKey() << std::endl;
			}

			break;
		}
	}
}