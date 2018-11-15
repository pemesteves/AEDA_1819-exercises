# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
	stack<T> valores;
	stack<T> minimos;
public:
	StackExt() {};
	bool empty() const;
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

template <class T>
bool StackExt<T>::empty() const {
	return valores.empty();
}

template <class T>
T& StackExt<T>::top() {
	T *novo = new T();
	if(!valores.empty()){
		*novo = valores.top();
	}
	return *novo;
}

template <class T>
void StackExt<T>::pop() {
	if(!valores.empty()){
		if(valores.top() == minimos.top())
			minimos.pop();
		valores.pop();
	}
}

template <class T>
void StackExt<T>::push(const T& val) {
	if(valores.empty()){
		minimos.push(val);
	}
	else{
		if(val <= minimos.top())
			minimos.push(val);
	}
	valores.push(val);
}

template <class T>
T& StackExt<T>::findMin() {
	T *novo = new T();
	if(!minimos.empty())
		*novo = minimos.top();
	return novo;
}
