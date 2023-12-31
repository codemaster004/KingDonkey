//
// Created by Filip Dabkowski on 29/12/2023.
//

#ifndef KINGDONKEY_LISTSET_H
#define KINGDONKEY_LISTSET_H

template<typename T>
class Node {
public:
	T value;
	Node *before = nullptr;
	Node *after = nullptr;

	Node() = default;

	explicit Node(const T &newValue) : value(newValue) {}
};

template <typename T>
class ListSet {
private:
	Node<T> *head = nullptr;
	Node<T> *tail = nullptr;

	/**
	 * @brief Append a new node with the given value after the specified node in the ListSet.
	 *
	 * @param node The node after which the new node should be appended.
	 * @param value The value to be stored in the new node.
	 */
	void appendNode(Node<T> *node, T &value) {
		auto newNode = new Node<T>(value);
		newNode->after = tail;
		newNode->before = node;
		tail->before = newNode;
		node->after = newNode;
	}

	/**
	 * @brief Frees the memory allocated for a linked list node and its subsequent nodes.
	 *
	 * This function deletes the given `node` and all the subsequent nodes in the linked list.
	 * It iterates through each node, storing the next node in a temporary variable, and deletes the
	 * current node.
	 *
	 * @tparam T The type of value stored in the node
	 * @param node The node to start freeing from
	 */
	void freeNode(Node<T> *node) {
		while (node != nullptr) {
			Node<T> *nextNode = node->after;
			delete node;
			node = nextNode;
		}
	}

public:
	ListSet() {
		head = new Node<T>();
		tail = new Node<T>();
		tail->before = head;
		head->after = tail;
	}

	class Iterator {
	private:
		Node<T>* current;

	public:
		explicit Iterator(Node<T>* node) : current(node) {}

		T& operator*() const {
			return current->value;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current = current->after;
			}
			return *this;
		}

		bool operator==(const Iterator& other) const {
			return current->value == other.current->value;
		}

		bool operator!=(const Iterator& other) const {
			return current->value != other.current->value;
		}
	};

	Iterator begin() {
		return Iterator(head->after);
	}

	Iterator end() {
		return Iterator(tail);
	}

	/**
	 * @brief Appends a value to the ListSet.
	 *
	 * This method appends the given value to the ListSet if it is not already present in the set.
	 * It does this by iterating through the list and checking if the value already exists.
	 * If the value is not found, a new node with the value is appended to the list.
	 *
	 * @tparam T The type of value to be appended
	 * @param value The value to be appended
	 */
	void append(T &value) {
		Node<T>* temp = head;
		while (temp->after != nullptr) {
			if (temp->value == value)
				return;

			temp = temp->after;
		}
		appendNode(temp->before, value);
	}

	ListSet<T> &extend(ListSet<T> &values) {
		for (T value : values) {
			append(value);
		}
		return values;
	}

	/**
	 * @brief Removes the first occurrence of the specified value from the ListSet.
	 *
	 * @param value The value to be removed.
	 */
	void remove(T &value) {
		// todo: implement when needed
	}

	/**
	 * @brief Clears the ListSet by freeing the memory allocated for all nodes.
	 *
	 * This function frees the memory allocated for all nodes in the ListSet.
	 */
	void clear() {
		freeNode(head);
	}

	~ListSet() {
		clear();
	};
};

#endif //KINGDONKEY_LISTSET_H