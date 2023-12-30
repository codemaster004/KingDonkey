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

	void appendNode(Node<T> *node, T &value) {
		auto newNode = new Node<T>(value);
		newNode->after = tail;
		newNode->before = node;
		tail->before = newNode;
		node->after = newNode;
	}

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

	void remove(T &value) {
		// todo: implement when needed
	}

	void clear() {
		freeNode(head);
	}

	~ListSet() {
		clear();
	};
};

#endif //KINGDONKEY_LISTSET_H