struct cell {
	int x, y, parentX, parentY;
	char c;
	double f, g;
	bool visited;
};

class MinHeap {
	cell* heapArray;
	int capacity;
	int heapSize;
public:
	MinHeap(int capacity) {
		this->heapSize = 0;
		this->capacity = capacity;
		this->heapArray = new cell[capacity];
	}
	void MinHeapify(int i) {
		int l = left(i);
		int r = right(i);

		int smallest = i;
		if (l<heapSize && heapArray[l].f < heapArray[i].f)
		{
			smallest = l;
		}
		if (r<heapSize && heapArray[r].f < heapArray[smallest].f)
		{
			smallest = r;
		}
		if (smallest != i)
		{
			swap(heapArray[i], heapArray[smallest]);

			MinHeapify(smallest);
		}
	}
	void swap(cell &element1, cell &element2) {
		cell temp = element1;
		element1 = element2;
		element2 = temp;
	}
	int parent(int i) { return (i-1)/2; }

	int left(int i) { return (2 * i + 1); }
	
	int right(int i) { return (2 * i + 2); }

	cell extractMin() {
		if (heapSize <= 0)
		{
			return {0, 0, 0, 0, 'n', 0.0, 0.0};
		}
		if (heapSize == 1)
		{
			heapSize--;
			return heapArray[0];
		}
		cell root = heapArray[0];
		heapArray[0] = heapArray[heapSize - 1];
		heapSize--;
		MinHeapify(0);

		return root;
	}
	void insertKey(cell k) {
		if (heapSize == capacity)
		{
			cell* temp = new cell[2 * capacity];
			for (int i = 0; i < capacity; i++)
			{
				temp[i] = heapArray[i];
			}
			delete[] heapArray;
			capacity *= 2;
			heapArray = temp;
		}

		int i = heapSize;
		heapArray[heapSize++] = k;
		while (i!=0 && heapArray[parent(i)].f > heapArray[i].f)
		{
			swap(heapArray[i], heapArray[parent(i)]);
			i = parent(i);
		}
	}
	bool isInHeap(cell lf) {
		for (int i = 0; i < heapSize; i++)
		{
			cell current = heapArray[i];
			if (current.x == lf.x && current.y == lf.y)
			{
				return true;
			}
		}
		return false;
	}
	int getSize() {
		return heapSize;
	}
	void deleteHeap() {
		delete[] heapArray;
	}

};

class MinHeapG {
	cell* heapArray;
	int capacity;
	int heapSize;
public:
	MinHeapG(int capacity) {
		this->heapSize = 0;
		this->capacity = capacity;
		this->heapArray = new cell[capacity];
	}
	void MinHeapify(int i) {
		int l = left(i);
		int r = right(i);

		int smallest = i;
		if (l < heapSize && heapArray[l].g < heapArray[i].g)
		{
			smallest = l;
		}
		if (r < heapSize && heapArray[r].g < heapArray[smallest].g)
		{
			smallest = r;
		}
		if (smallest != i)
		{
			swap(heapArray[i], heapArray[smallest]);

			MinHeapify(smallest);
		}
	}
	void swap(cell& element1, cell& element2) {
		cell temp = element1;
		element1 = element2;
		element2 = temp;
	}
	int parent(int i) { return (i - 1) / 2; }

	int left(int i) { return (2 * i + 1); }

	int right(int i) { return (2 * i + 2); }

	cell extractMin() {
		if (heapSize <= 0)
		{
			return { 0, 0, 0, 0, 'n', 0.0, 0.0 };
		}
		if (heapSize == 1)
		{
			heapSize--;
			return heapArray[0];
		}
		cell root = heapArray[0];
		heapArray[0] = heapArray[heapSize - 1];
		heapSize--;
		MinHeapify(0);

		return root;
	}
	void insertKey(cell k) {
		if (heapSize == capacity)
		{
			cell* temp = new cell[2 * capacity];
			for (int i = 0; i < capacity; i++)
			{
				temp[i] = heapArray[i];
			}
			delete[] heapArray;
			capacity *= 2;
			heapArray = temp;
		}

		int i = heapSize;
		heapArray[heapSize++] = k;
		while (i != 0 && heapArray[parent(i)].g > heapArray[i].g)
		{
			swap(heapArray[i], heapArray[parent(i)]);
			i = parent(i);
		}
	}
	int getSize() {
		return heapSize;
	}
	void deleteHeap() {
		delete[] heapArray;
	}

};