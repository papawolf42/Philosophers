# 1부터 10000까지 합 구하기

- 등차급수를 기억난다면 쉽게 이 합을 구할 수 있다.
  - 1 + 10000 +
  - 2 + 9999 +
  - ...(중략)
  - 4999 + 5002 +
  - 5000 + 5001
- 이므로 10001 * 5000
- 50005000 이다.
- 1 부터 100까지 하고 싶은데, 멀티쓰레드 중 동시성 문제를 확인하고 싶어서임.
- 동시성 문제(동기화 문제) : 자원을 공유하는 병렬 처리 시스템에서 의도하지 않은 데이터 변질이 발생하는 것.



# prog1: 일반적인 프로세스 만들기.

- sum 함수를 따로 뺴지 않고, main문에 만들었다.
- 다만 thread를 나누면 줄어드는 시간을 느끼기 위해서, usleep 함수를 사용하였다.
- usleep(200)이면 0.2ms를 쉬게되며, 1만번 반복하므로 2000ms, 즉 2초를 쉰다.
- 체감상 출력까지 3초정도 걸리는 듯 하다. 이는 연산에 수행되는 시간도 있겠지만, 다른 요소들이 속도에 영향을 미치는 듯 하다.



# prog2: 자원을 공유하지 않는 멀티 스레드 만들기.

- 스레드 수 만큼 변수를 만들어준다. 
- 각 스레드는 각각의 변수를 가진다.



# prog3: 자원을 공유하는 멀티 스레드 만들기.

- sum을 공유한다. 그렇기에 동시성 문제를 확인할 수 있다.

# prog4: prog3에 뮤텍스를 적용하여, 공유 자원 보호하기.





# pthread_detach는 뭐지?

- https://www.morenice.kr/75
- 쓰레드의 자원을 해제하여 종료하는 흐름

# gettimeofday는 뭐지?

- 이 함수는 time 함수와 매우 비슷하지만, µs(마이크로초) 단위의 시간까지 리턴해준다.
  https://www.joinc.co.kr/w/man/2/gettimeofday
- 이 과제에서는 ms(10⁻³s)를 subject에서 사용하는데
- usleep은 µs(10⁻⁶s) 범위로 지정한다.
- 



# Mutex가 binary semapore(이진 세마포어)라면 식사하는 철학자들의 문제에서 세마포어가 필요할까?

- 뮤텍스 = 이진 세마포어, 딱 이 범위만 구현하면 된다.



# (의문) 철학자가 포크를 집기위해 뮤텍스에서 기다리다가 죽으면 그 죽음을 어떻게 감시하고 출력하지???

- 감시 스레드라는 것을 두는 방식도 좋을 것 같음! https://42born2code.slack.com/archives/CU6MU5TB7/p1616728422101800?thread_ts=1616709923.099400&cid=CU6MU5TB7



# (의문) 감시스레드가 철학자의 죽음을 감지한 경우, 어떻게 철학자 스레드를 종료시키지??????



# 상태마다 색을 다르게 지정하기

- <span style='color:yellow'>포크 집기</span>
- <span style='color:green'>먹기</span>
- <span style='color:cyan'>잠자기</span>
- <span style='color:magenta'>생각하기</span>
- <span style='color:red'>굶어죽음</span>

# tip

- 멀티쓰레드의 경우 디버깅이 매우 어렵다. 디버깅보다는 디버깅 메시지를 이용하자
  https://codingcoding.tistory.com/12
- pthread_detach의 경우 쓰레드를 메인 쓰레드에서 분리한다. pthread_join와 같이 자원을 회수하는 것은 마찬가지이지만, 메인쓰레드와 분리되는 점이 다르다.
  https://d-yong.tistory.com/1
- 



# slack tip

- 출력이 꼬이지 않으려면, write보다는 printf를 사용하라.
  The status printed should not be scrambled or intertwined with another philosopher's status.
  write를 쓰게되면, stdout에서 스레드간 경쟁이 일어나므로, 출력이 꼬이게 된다.
  write에 mutex를 걸어도 되지만, 그보단 printf를 쓰는게 나아보임.
  https://42born2code.slack.com/archives/CU6MU5TB7/p1614413755376100
- main에서 argv로 받는 인자들은 그 최소값이 평가표에 특정되어 있다. 단 5번째 인자인 [최소한의 식사 수]는 그 특정값이 지정되어 있지 않다.
  https://42born2code.slack.com/archives/CU6MU5TB7/p1624363876071400
- 2021.6월 업데이트 이후, 철학자가 1명이 들어온 경우 무조건 죽어야하는 검사 항목이 평가표에 추가됨.
  https://42born2code.slack.com/archives/CU6MU5TB7/p1623927465379900?thread_ts=1623919614.373400&cid=CU6MU5TB7
- [생각해볼 거리] 철학자는 식사 도중에 죽을 수 있는가?
  maybe no. https://42born2code.slack.com/archives/CU6MU5TB7/p1623919614373400
- 프로그램이 문제를 발생시키는 경우는 대부분 철학자의 수가 다수로 주어졌을 때이다. 
  평가표에서는 최대 199명이라고 한다. https://42born2code.slack.com/archives/CU6MU5TB7/p1616709923099400
- number_of_times_each_philosopher_must_eat 는 가장 적게 먹은 철학자가 먹은 횟수를 채웠을 때
- `-fsanitize=address`  옵션을 주면 지연시간이 빠르게 누적되므로 조심 
  https://42born2code.slack.com/archives/CU6MU5TB7/p1616072925210700?thread_ts=1616063061.193600&cid=CU6MU5TB7
- 