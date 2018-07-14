# DataStructure

1. ArrayList           - 2018 .07. 04
2. LinkedList          - 2018. 07. 05
3. LinkedList_add      - 2018. 07. 05
4. CircularList        - 2018. 07. 06
5. DoublyList          - 2018. 07. 06
6. Polynomia           - 2018. 07. 07
7. ArrayStack          - 2018. 07. 09
8. LinkedStack         - 2018. 07. 09
9. StackUtilization    - 2018. 07. 10 - 11
10. ArrayQueue         - 2018. 07. 12
11. ArrayCircularQueue - 2018. 07. 12

배열리스트
-배열값을 지정한다(maxCount)
-배열리스트 자체를 생성하는 것과 배열리스트의 배열을 생성하는 과정이 필요하다.
-배열을 모두 초기화한다
-새로운 자료의 추가시 현재 있는 배열들을 이동하는 과정이 필요하다.
-배열 이동시 가장 오른쪽(pList->currentCount-1)부터 사용자에게 입력받은 인덱스값(position)까지 이동
-배열을 이동 후에 자료를 추가한다.
-기존의 자료를 제거시 제거한 위치의 다음 배열값들은 한칸씩 왼쪽으로 이동해야한다.(pList->pData[i] = pList->pData[i+1])

연결리스트
-리스트의 값을 얻고자 할 경우 사용자로부터 입력받은 위치의 노드까지 순회하는 과정이 필요(for(i = 0;i <= position; i++))
-새로운 노드를 추가할 경우 입력 받은 위치의 노드까지 순회하는 과정이 필요하다(for(i = 0; i<position; i++))
-이전 노드 포인터변수 pPreNode, 새로운 노드 포인터 변수 pNewNode가 필요함.
-새로운 노드의 처리는 1. 노드 생성 2. 생성한 노드의 pLink처리 3. 이전 노드의 pLink처리 순서로 진행된다
-노드의 제거또한 순회하는 과정이 필요하다
-1. pDelNode = pPreNode->Link, 이전 노드의 다음 링크 노드를 저장. (이전 노드의 다음 노드가 제거할 노드)
-2. pPreNode->pLink = pDelNode->pLink, 이전 노드의 pLink값 재지정
-위의 과정을 재풀이하면 pPreNode->pLink = pPreNode->pLink->pLink이다. 
-3. free(pDelNode), 노드 제거
-연결리스트의 현재 데이터를 모두 출력하고자 할 경우 getLinkedListData() 함수를 사용하여
 출력하는 방법이 있지만, getLinkedListData()함수의 경우 호출할 때마다 처음부터 순회해야 하므로
 실행시간이 오래걸린다. 순회하지 않고 데이터를 바로바로 출력하기 위해 pNode에 처음 헤더 노드의 주소를 저장한 후
 pNode->data를 출력 함수 내에서 바로 출력하고 다음 노드로 이동하는 과정을 반복한다.
-두개의 리스트를 이어주는 concat()함수는 pListA가 비어있을 경우 pListA의 헤더노드가 pListB의 첫 번째 노드를 가르키게 된다.
 
원형리스트
-연결리스트와의 차이점은 새로운 노드 추가시 리스트가 비어있다면 pLink가 자기 자신을 가르킨다(pNewNode->pLink = pNewNode)
-후처리가 필요하지 않은 이유는 이미 리스트가 비어있다는 if문에서 위와같은 연산으로 순환구조가 만들어졌기 때문
-리스트에서 첫번째 자료를 제거하여 빈 리스트가 된 경우(pList->currentCount == 0) 헤더 노드의 pLink를 NULL로 초기화하여야 한다.

이중연결리스트
-하나의 노드에는 현재노드의 이전노드를 가르키는 pLLink, 다음노드를 가르키는 pRLink가 필요하다.
-처음 리스트 생성시 pLLink와 pRLink는 헤더노드 자기 자신을 가르킨다.
-원형리스트와 이중연결리스트의 차이점은 원형리스트는 마지막 노드의 다음 노드는 첫 번째 노드이지만
 이중연결리스트의 경우 마지막노드의 다음노드는 첫 번째 노드가 아닌 헤더 노드라는 점이다.
-이중연결리스트의 속성
 1. 마지막 노드의 다음 노드 = 헤더노드
 2. 헤더 노드의 이전 노드 = 마지막노드
 3. pNode = pNode->pRLink-pLLink = pNode->pLLink->pRLink

배열스택
-배열 스택또한 배열 리스트와 마찬가지로 최대값(maxCount)가 필요하다.
-스택의 pop연산은 배열 스택의 노드 포인터를 반환한다. 리스트는 데이터만 반환한다.
 > ArrayStackNode 포인터 변수를 만들어서 데이터 저장후 반환해야 한다.
 > pReturn->data = pStack->pData[pStack->currentCount-1].data
-peek연산은 배열 스택의 주소를 반환한다. (pReturn = &(pStack->pData[pStack->currentCount-1]))

포인터스택
-pop 연산은 메인함수에서 free로 메모리 해제를 해주어야 함.
-peke 연산은 free로 메모리 해제를 하지 않는다.

배열 큐
- 큐에는 front, rear의 개념이 들어간다
- front에서는 삭제만, rear에서는 입력만 할 수 있다.
- 배열 큐는 front가 가르키는 인덱스의 데이터를 삭제한 후 front가 +1된다.
  따라서 데이터가 삭제된 곳의 인덱스는 사용할 수가 없다는 단점이 있다.
- 배열에서 비어있는 곳이 있더라도 front로 데이터를 삭제하는 특성상 데이터를 입력할 수
  없으므로 isArrayQueueFull함수에서 2가지의 조건이 들어가야 한다.
  1. pStack->currentCount == pStack->maxCount // 최대 개수와 현재 개수가 같으면 포화상태
  2. pStack->rear == pStack->maxCount-1 // rear가 배열의 맨 끝 인덱스에 있다면 포화상태
 
배열 원형큐
- 배열 큐의 front연산에 대한 단점을 보완하는 방법으로 front와 rear의 증가값을
  +1씩 주는 것이 아닌 (front+1) % maxCount 와 같이 공식을 대입하여 다시 0번의
  인덱스로 회귀하는 방법을 사용하는 방법
- 배열 큐와 다르게 isArrayQueueFull 함수에서 pStack->currentCount == pStack->maxCount의 비교만 하여 판단
- display()의 for문에서 조건으로 rear를 사용할 수 없다. 논리적 연산으로 front와 rear의 값이 계산되기 떄문에
  rear의 값이 front보다 작을수 있기 때문이다. 따라서, 조건문은 front위치부터 시작하여
  저장된 자료 개수만큼 한 칸씩 이동하여 자료를 출력하게 된다.
  > i <= pQueue->front + pQueue->currentCount

연결큐
-노드 삽입 시 큐가 비어있을 경우까지 고려해야 한다.
-큐가 비어있을 경우 front와 rear 모두 새로 생성한 노드를 가르켜야 함
