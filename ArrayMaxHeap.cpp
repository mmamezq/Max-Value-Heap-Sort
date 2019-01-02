#include "ArrayMaxHeap.h"

#ifndef ARRAY_MAXHEAP_CPP
#define ARRAY_MAXHEAP_CPP


template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap()
{
    itemCount = 0;
    items = new ItemType[DEFAULT_CAPACITY];
    maxItems = DEFAULT_CAPACITY;
}

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[],
                                     const int arraySize)
{
    itemCount = arraySize;
    items = new ItemType[arraySize];
    maxItems = arraySize;
    for (int index = 0; index < arraySize; index++)
        items[index] = someArray[index];
    heapCreate();
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::swap(int first, int second)
{
	ItemType temp = items[first];
	items[first] = items[second];
	items[second] = temp;
}
template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
	int leftChild = 2 * nodeIndex + 1;
	if (leftChild >= itemCount)
		return -1;
	return leftChild;
}

// Returns the array index of the right child (if it exists)
template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(const int nodeIndex) const
{
	int rightChild = 2 * nodeIndex + 2;
	if (rightChild >= itemCount)
		return -1;
	return rightChild;
}

// Returns the array index of the parent node
template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(int nodeIndex) const
{
	if (nodeIndex == 0)
		return nodeIndex;
	else
		return (nodeIndex - 1) / 2;
}

// Tests whether this node is a leaf
template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const
{
	return nodeIndex >= itemCount / 2;
}

// Converts a semiheap to a heap
template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int subTreeRootIndex)
{
	int largerChildIndex = 0,
		rightChildIndex;
    // Recursively trickle the item at index root down to its proper position by swapping
    // it with its larger child, if the child is larger that the item. If the item is at a leaf,
    // nothing needs to be done
    if (!isLeaf(subTreeRootIndex))
    {
        // The root must have a left child; assume it is the larger child
        largerChildIndex = 2 * subTreeRootIndex + 1;                        // Left child index

        if (getRightChildIndex(subTreeRootIndex) > 0)
        {
            rightChildIndex = largerChildIndex + 1;               // Right child index
            if (items[rightChildIndex] > items[largerChildIndex])
                largerChildIndex = rightChildIndex;                 // Larger child index
         }
         // If the item in the root is smaller than the item in the larger child, swap items

        if (items[subTreeRootIndex] < items[largerChildIndex])
        {
			swap(subTreeRootIndex, largerChildIndex);
            // Transform the semiheap rooted at largerChildIndex into a heap
            heapRebuild(largerChildIndex);
        }
    }
    // Else root is a leaf, so you are done

}

// Creates a heap from an unordered array
template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
	for (int index = itemCount / 2; index >=0; index--)
    {
		// Assertion: The tree rooted at index is a semiheap
		heapRebuild(index);
		// Assertion: The tree rooted at index is a heap
    }

}



//template<class ItemType>
//ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
//{
//	delete [] items;
//}


// HeapInterface Public Methods:
template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
	return itemCount;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
	int height = 0;
	if (itemCount > 0)
	  height = int( log((double) itemCount)/log(2.0) ) + 1;
	return height;
}

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
	return items[0];
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
	bool inPlace = false;
	int newDataIndex = itemCount,
		parentIndex;

	if (itemCount >= maxItems)
		return false;

	// Insert newData into the bottom of the tree
	items[itemCount] = newData;

	// Trickle new item up to the appropriate spot in the tree
	while ( (newDataIndex >= 0) && !inPlace)
	{
		parentIndex = (newDataIndex - 1) / 2;
		if (items[newDataIndex] <= items[parentIndex])
			inPlace = true;
		else
		{
			swap(newDataIndex, parentIndex);
			newDataIndex = parentIndex;
		}
	}
	itemCount++;
	return true;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
	if (itemCount == 0)
		return false;

	// Copy the item from the last node and place it into the root
	items[0] = items[itemCount - 1];

	// Remove the last node
	itemCount--;

	// Rebuild heap
	heapRebuild(0);

	return true;

}

template<class ItemType>
void ArrayMaxHeap<ItemType>::sort(ItemType someArray[], ArrayMaxHeap heap, int arraySize){

    for( int i = arraySize-1; i >= 0; i--){
        someArray[i] = heap.peekTop();
        heap.remove();
    }

}

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
	itemCount = 0;
}
#endif