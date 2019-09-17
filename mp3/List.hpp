/**
* @file list.cpp
* Doubly Linked List (MP 3).
*/


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
  return List<T>::ListIterator(nullptr);
}

/**
* Destroys the current List. This function should ensure that
* memory does not leak on destruction of a list.
*/
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
* Destroys all dynamically allocated memory associated with the current
* List class.
*/
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* temp = head_;
  for (int i = 0; i < length_; i++){
    ListNode* current = temp;
    temp = temp->next;
    delete current;
  }
  head_ = NULL;
  tail_ = NULL;
  //    delete length_;
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
  if (head_ != NULL){
    ListNode* temp = new ListNode(ndata);
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    length_ = length_ + 1;
    temp->prev = NULL;
    //        std::cout<<length_<<std::endl;
  }
  else {
    ListNode* temp = new ListNode(ndata);
    head_ = temp;
    tail_ = temp;
    length_ = 1;
    //        std::cout<<length_<<std::endl;

  }
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
  if (head_ != NULL){
    ListNode* temp = new ListNode(ndata);
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
    length_ = length_ + 1;
  }
  else {
    ListNode* temp = new ListNode(ndata);
    head_ = temp;
    tail_ = temp;
    length_ = 1;

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
  /// @todo Graded in MP3.1
  if (startPoint ==  NULL || endPoint == NULL || startPoint == endPoint ){
    //std::cout<<"invalid start and end \n";
    return;
  }
  ListNode* start = startPoint;
  ListNode* startPrev = startPoint->prev;
  ListNode* end = endPoint;
  ListNode* endNext = endPoint->next;
  do{
    ListNode * temp = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = temp;
    startPoint = startPoint->prev;
  }
  while(startPoint != endPoint);
  ListNode * temp = startPoint->prev;
  startPoint->prev = startPrev;
  startPoint->next = temp;
  endPoint = start;
  endPoint->next = endNext;
  if(startPrev == NULL){
    head_ = startPoint;
  }
  else{
    startPrev->next = startPoint;
  }
  if(endNext == NULL){
    tail_ = endPoint;
  }
  else{
    endNext->prev = endPoint;
  }

}

/**
* Reverses blocks of size n in the current List. You should use your
* reverse( ListNode * &, ListNode * & ) helper function in this method!
*
* @param n The size of the blocks in the List to be reversed.
*/
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (head_ == NULL){
    return;
  }
  ListNode* startPoint = head_;
  ListNode* endPoint = startPoint;
  do{
    endPoint = startPoint;
    for (int i = 0; i < n-1; i++){
      if (endPoint->next != NULL){
        endPoint = endPoint->next;
      }
    }
    reverse(startPoint, endPoint);
    startPoint = endPoint->next;
  }
  while(endPoint->next != NULL && startPoint->next != NULL);
  return;
}

/**
* Modifies the List using the waterfall algorithm.
* Every other node (starting from the second one) is removed from the
* List, but appended at the back, becoming the new tail. This continues
* until the next thing to be removed is either the tail (**not necessarily
* the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
* Note that since the tail should be continuously updated, some nodes will
* be moved more than once.
*/
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (head_ == NULL || head_->next == NULL){
    return;
  }
  ListNode* keep = head_;
  ListNode* move = head_->next;
  do {
    keep->next = move->next;
    keep->next->prev = keep;
    move->prev = tail_;
    move->next = NULL;
    tail_->next = move;
    tail_ = move;
    keep = keep->next;
    move = keep->next;
  }
  while(move != NULL && move != tail_);
}

/**
* Splits the given list into two parts by dividing it at the splitPoint.
*
* @param splitPoint Point at which the list should be split into two.
* @return The second list created from the split.
*/
template <typename T>
List<T> List<T>::split(int splitPoint) {
  if (splitPoint > length_)
  return List<T>();

  if (splitPoint < 0)
  splitPoint = 0;

  ListNode * secondHead = split(head_, splitPoint);

  int oldLength = length_;
  if (secondHead == head_) {
    // current list is going to be empty
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
  } else {
    // set up current list
    tail_ = head_;
    while (tail_ -> next != NULL)
    tail_ = tail_->next;
    length_ = splitPoint;
  }

  // set up the returned list
  List<T> ret;
  ret.head_ = secondHead;
  ret.tail_ = secondHead;
  if (ret.tail_ != NULL) {
    while (ret.tail_->next != NULL)
    ret.tail_ = ret.tail_->next;
  }
  ret.length_ = oldLength - splitPoint;
  return ret;
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
* @param start The node to start from.
* @param splitPoint The number of steps to walk before splitting.
* @return The starting node of the sequence that was split off.
*/
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if (splitPoint == 0 || start == NULL){
    return start;
  }
  ListNode* newStart = start;
  for (int i = 0; i < splitPoint; i++){
    newStart = newStart->next;
  }
  newStart->prev->next = NULL;
  newStart->prev = NULL;
  return newStart;
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
  if (first == NULL || second == NULL){
    return NULL;
  }
  if (first == second){
    return first;
  }
  /*if (first->next == NULL && second->next == NULL && second->prev == NULL && first->prev == NULL){
    if(first->data < second->data){
      first->next = second;
      second->prev = first;
      return first;
    }
    if(second->data < first->data){
      second->next = first;
      first->prev = second;
      return second;
    }
  }*/
  ListNode* currentfirst = first;
  ListNode* currentsecond = second;
  ListNode* newHead = first;
  ListNode* result = newHead;
  if(first->data < second->data){
		currentfirst = first->next;
	}
	else{
		newHead = second;
		currentsecond = second->next;
	}
	while(currentfirst != NULL && currentsecond != NULL){
		if(currentfirst->data < currentsecond->data||currentsecond == NULL){
			result->next = currentfirst;
			currentfirst->prev = result;
			result = currentfirst;
			currentfirst = currentfirst->next;
		}
		else{
			result->next = currentsecond;
			currentsecond->prev = result;
			result = currentsecond;
			currentsecond = currentsecond->next;
		}
	}
	if(currentfirst == NULL){
		result->next = currentsecond;
		currentsecond->prev = result;
	}
	else{
		result->next = currentfirst;
		currentfirst->prev = result;
	}
	second = NULL;
	return newHead;
}


/**
* Sorts the current list by applying the Mergesort algorithm.
*/
template <typename T>
void List<T>::sort() {
  if (empty())
  return;
  head_ = mergesort(head_, length_);
  tail_ = head_;
  while (tail_->next != NULL)
  tail_ = tail_->next;
}

/**
* Sorts a chain of linked memory given a start node and a size.
* This is the recursive helper for the Mergesort algorithm (i.e., this is
* the divide-and-conquer step).
*
* @param start Starting point of the chain.
* @param chainLength Size of the chain to be sorted.
* @return A pointer to the beginning of the now sorted chain.
*/
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode* result = start;
  if (chainLength == 1){
    start->next = NULL;
    start->prev = NULL;
    std::cout<<"chainlegth is 1 \n";
    return start;
  }
  else{
    ListNode* halfway = start;
    for (int i = 0; i < chainLength/2; i++){
      halfway = halfway->next;
      std::cout<<"for loop is stuck \n";
    }
      std::cout<<"for loop is fine \n";
    halfway->prev->next = NULL;
    halfway->prev = NULL;
    start = mergesort(start, (chainLength/2));
    halfway = mergesort(halfway, (chainLength-(chainLength/2)));
    std::cout<<"merge is stuck \n";
    result = merge(start, halfway);
    std::cout<<"merge is fine \n";
  }
  return result;
}
