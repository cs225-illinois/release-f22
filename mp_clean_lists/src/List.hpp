/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* listWalker;
  ListNode* temp;
  listWalker = head_;

  while (listWalker != NULL) {
    temp = listWalker;
    listWalker = listWalker->next;
    delete temp;
  }
  head_ = tail_ = temp = NULL;
  length_ = 0;


}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
   /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (head_ == NULL){
    head_ = newNode;
    tail_ = newNode;
  } else {
    newNode -> next = head_;
    head_->prev = newNode;
    head_ = head_->prev;
  }


  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  if (length_ == 0) {
    head_ = newNode;
    tail_ = newNode;
    length_++;
  }
  else {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = tail_->next;
    length_++;

  }
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (splitPoint == 0 ) {return start;}
  ListNode* walker = start;
  ListNode* temp;
  for (int i = 0; i < splitPoint; i++) {
    temp = walker;
    walker = walker->next;
  }
  temp->next = NULL;

  return walker;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (length_ < 3) {return;}
  ListNode* listWalker = head_;
  for (int i = 0; (i+2) < length_; i+=2) {
    ListNode* start = listWalker;
    ListNode* mid = listWalker->next;
    ListNode* end = listWalker->next->next;
    ListNode* anchor_l =(start == head_) ? NULL : start->prev;
    ListNode* anchor_r = (end == tail_) ? NULL :  end->next;
    if (anchor_l != NULL) {
      anchor_l->next = mid;
      mid->prev = anchor_l;
    } else {
      mid->prev = NULL;
      head_ = mid;
    }
    end->next = start;
    start->prev = end;

    if (anchor_r != NULL) {
      start->next = anchor_r;
      anchor_r->prev = start;
    } else {
      start->next = NULL;
      tail_ = start;
    }
    listWalker = listWalker->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (startPoint == endPoint) return;
  //Last node on either side not cut
  ListNode* anchor_l = startPoint->prev;
  ListNode* anchor_r = endPoint->next;
  //List walker for reading backwards
  ListNode* listWalker = startPoint;
  ListNode* temp = NULL;
  //references to start and end point, used to switch their positions
  //at end of function.
  ListNode* startRef = startPoint;
  ListNode* endRef = endPoint;

  //Walk through the list backwards
  while (listWalker != endPoint) {
    temp = listWalker->prev;
    listWalker->prev = listWalker->next;
    listWalker->next = temp;
    listWalker = listWalker->prev;
  }

  //Reconnect to the anchor points
  listWalker->next = listWalker->prev;
  listWalker->prev = anchor_l;
  startPoint->next = anchor_r;

  //Clean up any incongruities with head_ and tail_ ptrs.
  if (anchor_l != NULL) {
    anchor_l->next = endPoint;
  } else {
    head_ = endPoint;
  }

  if (anchor_r != NULL) {
    anchor_r->prev = startPoint;
  
  } else {
    tail_ = startPoint;
  }
  //Finally reconnect the list using the two references from the begininng.
  startPoint = endRef;
  endPoint = startRef;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  if (n == 1) {
    return;
  }
  if (n == length_) {
    reverse();
  } else {
    ListNode* listWalker = head_;
    for (int i = 0; (i + n) < length_; i+=(n - 1)) {
      ListNode* temp = listWalker;
      for (int j = 0; j < n-1; j++) {
        temp = temp->next;
      }
      ListNode* end = temp;
      reverse(listWalker, end);
      listWalker = end->next;
    }
  }

  
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first == NULL) {return second;}
  if (second == NULL) {return first;}
  if (first && second == NULL) {return NULL;}
  ListNode* firstWalker, *firstTemp;
  ListNode* secondWalker, *secondTemp;
  
  if (second->data < first->data) {
    ListNode* secondLower = second;
    second = first;
    first = secondLower;
  }
  //first will always have the lower head
  firstWalker = first;
  secondWalker = second;

  while (secondWalker != NULL) {
    secondTemp = secondWalker->next;

    while (firstWalker != NULL) {
      firstTemp = firstWalker->next;

      if (secondWalker->data < firstWalker->data) {
        secondWalker->next = firstWalker;
        firstWalker->prev->next = secondWalker;
        secondWalker->prev = firstWalker->prev;
        firstWalker->prev = secondWalker;
        break;
      } else if (firstWalker == NULL && secondWalker != NULL) {
        firstWalker->next = secondWalker;
        secondWalker->prev = firstWalker;
        break;
      } else {
        firstWalker = firstTemp;
      }
    }
    if (firstWalker->next == secondWalker) {break;}
    secondWalker = secondTemp;

  }



  return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
