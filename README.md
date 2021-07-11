# Index
- [Simple Calculator](#Simple-Calculator)
- [Single Cycle-MIPS](#Single-Cycle-MIPS)
- [MIPS Pipeline](#MIPS-Pipeline)
- [Emulator with Cache](#MIPS-Cache)

# Simple Calculator

## Description
 본 프로젝트는 Von Neumann architecture을 기반으로 한 Computing Model을 개발하는 프로젝트이다. 이 Computing Model은 기본적인 사칙연산 뿐만 아니라 내부 명령어인 M, C, J, B, H를 사용하여 간단한 연산과 레지스터의 동작을 수행할 수 있는 프로그램이다. 
 이번 프로젝트의 목표는 이 프로그램을 구현하면서 컴퓨터 내부 동작에 대해 이해를 하고 구현한 프로그램을 바탕으로 여러 연산을 수행해보면서 Von Neumann architecture와 ISA Model에 대해 이해하는 것이다.
 
## Requirements
- input.txt에 필요한 연산을 작성한 후, 그 파일을 읽어들이면서 시작한다.
- input.txt의 기본적인 형식은 다음과 같습니다. OPCODE operand1 operand2. 각각은 white space 중 space (' ')로 구분이 되어있다.
- input.txt는 줄바꿈 ('\n')혹은 종결 ('\0')로 각 연산을 구분한다. 
- 레지스터는 결과를 담는 R0부터 R9까지 총 열 개가 있다.
- operand에는 16진수 혹은 레지스터가 올 수 있다. 형식은 다음과 같다. "0xN, Rn. 이때 N은 0에서 F까지, n은 0~9까지"

## Instruction Set Architecture
#### 사칙 연산 명령어
 두 개의 operand를 인자로 갖는다. 이때, 두 개의 operand는 16진수 형태인 0x 형태, 혹은 레지스터에 저장된 값인 RN 형태로 올 수 있고 N은 0~9이다. (10개) 
- '+' (Add) : 두 개의 operand를 더한 값을 Reg R0에 저장하는 연산.
  - 형식 : + operand1 operand2
- '-' (Sub): 두 개의 operand를 뺀 값을 Reg R0에 저장하는 연산.
  - 형식 : - operand1 operand2
- '*' (Multiplication): 두 개의 operand를 곱한 값을 Reg R0에 저장하는 연산. 
  - 형식 : * operand1 operand2
- '/' (division): 두 개의 operand를 나눈 값을 Reg R0에 저장하는 연산이다. 이때, 나머지는 버리고 몫만 R0에 저장한다. 또한, 0으로 나눌 시 경고 메시지만을 출력한다. 
  - 형식 : / operand1 operand2
#### 레지스터 명령어
- 'M' (Move): operand1인 레지스터에 operand2를 저장하는 연산이다. 이때 operand1은 레지스터 형태, operand2는 16진수 형태이다.
  - 형식 : M operand1 operand2
- 'C' (Compare) : 두 개의 operand를 비교하는 연산이다. operand1 >= operand2 라면 R0 := 0, operand1 < operand2 라면 R0 := 1 이때, 두 operand는 16진수와 레지스터 형태 둘 다 가능하다.
  - 형식 : C operand1 operand2
#### 흐름 제어 명령어
- 'J' (Jump) : operand1번째 명령어줄로 이동하는 명령어이다. 이때 operand1은 16진수 형태만 가능하다. (operand2는 무시)
  - 형식 : J operand1
- 'B' (Brnach) : R0 = 1 이라면, operand1 번째 명령어가 실행된다. (operand2는 무시)
  - 형식 : B operand1
- 'H' (Halt) : 실행을 종료한다.
  - 형식 : H

## Environment
- 사용 언어 : C
- 개발 환경 : Linux
- 파일 정보 : main.c error_check.c decode.c execute.c calculator.h

## How to Compile
1. git clone을 하여 소스파일이 모두 있는 디렉토리에 위치한다.
2. vim input.txt 를 입력한 후 i또는 a또는 o를 눌러 입력 모드를 통해 알맞은 식을 입력한다.
3. 입력이 완료가 되면 ESC를 누른 후, :wq를 입력한 후 엔터를 쳐서 파일 저장한다.
4. 저장이 되었다면, gcc -Wall -Wextra -Werror *.c 를 입력한다.
4-1) 옵션을 추가해준 이유는 모호한 코딩에 대한 경고와 모든 경고에 대해 컴파일 에러를 처리하여 더욱 완성도 있는 코드를 증명하기 위함이다.
5. 컴파일이 잘되었다면 a.out 실행 파일이 생성되었을 것이다. ./a.out 을 입력하여 실행을 한 후, 결과를 확인한다.

## Exception Handling
- input.txt 파일을 불러오지 못하거나 빈 파일이라면 에러 메시지 출력 후 프로그램을 종료한다.
- 16진수 형태는 0x 다음으로 나오는 character 중에서 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F만 인정한다. 이외의 character는 모두 에러로 처리한다.
- 레지스터 형태는 R 다음으로 나오는 character 중에서 0, 1, 2, 3, 4, 5, 6, 7, 8, 9만 인정한다. 이외의 character는 모두 에러로 처리한다.
- input.txt에서 OPCODE에 대한 기본 형식 (OPCODE Operand1 Operand2 혹은 OPCODE Operand1)와 다른 형식이라면 에러 메시지 출력 후 프로그램을 종료한다. 아래의 형식과 OPCODE이외의 다른 모든 형식은 에러로 처리한다.
  - 사칙연산('+', '-', '*', '/')과 레지스터 명령어 'C'는 OPCODE Operand1 Operand2의 형식으로 Operand에는 16진수 형태와 레지스터 형태 모두 가능.
  - 흐름 제어 명령어 'J'와 'B'는 OPCODE Operand1의 형식으로 Operand에는 16진수 형태만 가능.
  - 레지스터 명령어 'M'은 OPCODE Operand1 Operand2의 형식으로 Operand1에는 레지스터 형태, Operand2에는 레지스터 형태와 16진수 형태 둘 다 가능.
  - 흐름 제어 명령어 'H'는 H 하나만 가능.
- '/' 연산 수행 시, Operand2가 0일 경우 0으로 나눌 수 없음에 대한 에러 메시지 출력 후 해당 연산을 종료한다.
- 흐름 제어 명령어 'J'와 'B' 실행 시 Operand1이 input.txt의 size, 즉, 파일의 라인 개수보다 크면 해당 라인으로 JUMP가 불가능 하므로 에러 메시지 출력 후 프로그램을 종료한다.
<br><br>

# Single Cycle MIPS

## Description
 본 프로젝트는 간단한 ISA를 가진 MIPS 시뮬레이터 프로그램을 구현하는 프로젝트이다. 이 프로그램은 input으로 들어온 실행 가능한 binary 파일의 각 명령어들을 해석하여 해당 소스코드의 결과와 동일한 결과를 얻는 것이 목표이다. 이 시뮬레이터에 포함된 ISA는 MIPS Green Sheet 의 CORE INSTRUCTION SET의 31개의 명령어 중 6개의 명령어(lbu, lhu, ll, sb, sc, sh)를 제외한 25개의 명령어와 JALR(Jump And Link using Register)이다. 각각의 명령어는 Single-Cycle MIPS를 따라 IF(Instruction Fetch), ID(Instruction Decode), EXE(EXEcution), MEM(MEMory access), WB(Write Back)의 다섯 단계를 거치는데, 이것은 실제 CPU와 동일하게 작동해야 한다. 본 프로젝트를 통해 컴퓨터 내부 동작과 Single Cycle에 대해 이해하는 것이 목표이다.
 
## Requirements
- MIPS binary program(input 디렉토리의 .bin파일)을 input(실행 파일의 인자)으로 한다.
- 실제 CPU 동작과 동일하게 구현해야 한다.
  - 레지스터 : R[0] ~ R[31]까지 존재하며 LR(R[31])과 SP(R[29])를 제외한 모든 레지스터는 0으로 초기화되어야 한다. LR과 SP의 초기값은 각각 0xFFFF:FFFF, 0x100:0000이다.
  - 메모리 : 메모리는 16MB이다. 단, Instruction memory와 data memory를 하나의 메모리로 구현한다.
  - PC : PC는 현재 명령어의 주소를 가지고 있는 레지스터로, 초기값은 프로그램의 시작주소인 0x0 이다. 각 명령어에 대응하여 PC는 0x0 부터 4씩 증가하며 PC가 0xFFFF:FFFF일 때 프로그램이 종료된다.
- 각 사이클마다 아키텍쳐 상태의 변화가 생긴다면 user visible architectural state인 PC, GPR, Memory에 대한 상태를 출력해야 한다.
- 명령어가 전부 실행되면, 다음과 같은 값들을 출력해야합니다.
	 - 최종 결과값 (R[2])
	 - 명령어 실행 횟수
	 - R-type 명령어 실행 횟수
	 - I-type 명령어 실행 횟수
	 - J-type 명령어 실행 횟수
	 - 메모리 액세스 명령어 실행 횟수
	 - branch 명령어 실행한 횟수

## Single-Cycle
- 명령어 하나 당 하나의 사이클이 돌아야 한다.
- OPCODE에 따라 Control Signals를 구한 후 MUX의 개념을 이용하여 Signal에 따라 각 명령어가 필요로 하는 단계에만 접근 가능하게 한다.
- JALR (Jump And Link using Register) 명령어를 구현해야 한다.
	 - rd에 리턴할 주소값을 저장하고 rs로 점프하는 R-type 명령어입니다.
	 - rd = 31, rs = 점프 타겟 레지스터, funct = 0x9, 나머지는 0입니다.
	 - JALR 명령어를 16진수로 하면 0x0?!0f809 입니다. 이때 '?'와 '!'는 미지수로 범위는 		다음과 같습니다. 
		 - 0 <= ? <= 3
		 - 0 <= ! <= E

## Environment
- 사용 언어 : C
- 개발 환경 : Linux
- 파일 정보 : src/main.c src/fetch.c src/decode.c src/execute.c src/memory_access.c src/write_back.c src/MUX.c src/single_cycle.h

## How to Compile
1. git clone을 하여 소스파일이 모두 있는 디렉토리(src)에 위치한다.
2. gcc -Wall -Wextra -Werror *.c -o single_cycle 를 입력하여 컴파일한다.
2-1) 옵션을 추가해준 이유는 모호한 코딩에 대한 경고와 모든 경고에 대해 컴파일 에러를 처리하여 더욱 완성도 있는 코드를 증명하기 위함이다.
3. 컴파일이 잘 되었다면 single_cycle 실행 파일이 생성되었을 것이다. ./single_cycle에 원하는 input 디렉토리의 binary 파일명을 입력하여 실행한 후, 결과를 확인한다.

## Exception Handling
- input 파일을 불러오지 못하거나 빈 파일이라면 에러 메시지 출력 후 프로그램을 종료한다.
- 명령어를 decode 할 때, opcode가 정해진 format이 아니라면 에러 메시지 출력
![image](https://user-images.githubusercontent.com/70425484/124956708-3588d780-e053-11eb-90a9-b00ab4f4e6a3.png)

<br><br>
# MIPS Pipeline

## Description
 본 프로젝트는 파이프라인을 이용하여 더 효율적인 성능을 가진 MIPS 시뮬레이터를 구현하는 프로젝트이다. 이 프로그램은 input으로 들어온 실행 가능한 binary 파일의 각 명령어들을 해석하여 해당 소스코드의 결과와 동일한 결과를 얻는 것이 목표이다. 이 시뮬레이터에 포함된 ISA는 MIPS Green Sheet 의 CORE INSTRUCTION SET의 31개의 명령어 중 6개의 명령어(lbu, lhu, ll, sb, sc, sh)를 제외한 25개의 명령어이다. 각각의 명령어는 Single-Cycle MIPS를 따라 IF(Instruction Fetch), ID(Instruction Decode), EXE(EXEcution), MEM(MEMory access), WB(Write Back)의 다섯 단계를 거치는데, 이것은 실제 CPU와 동일하게 작동해야 한다. 또한, 파이프라인에 의하여 연속적으로 명령어를 실행하는 sequential execution을 따라야하고 명령어간의 dependency를 파악하여 그것을 해결할 수 있어야 한다. 본 프로젝트를 통해 컴퓨터 내부 동작과 파이프라인, 명령어간의 dependency에 대해 이해하는 것이 목표이다.
 
## Requirements
- MIPS binary program(input 디렉토리의 .bin파일)을 input(실행 파일의 인자)으로 한다.
- 실제 CPU 동작과 동일하게 구현해야 한다.
  - 레지스터 : R[0] ~ R[31]까지 존재하며 LR(R[31])과 SP(R[29])를 제외한 모든 레지스터는 0으로 초기화되어야 한다. LR과 SP의 초기값은 각각 0xFFFF:FFFF, 0x100:0000이다.
  - 메모리 : 메모리는 16MB이다. 단, Instruction memory와 data memory를 하나의 메모리로 구현한다.
  - PC : PC는 현재 명령어의 주소를 가지고 있는 레지스터로, 초기값은 프로그램의 시작주소인 0x0 이다. 각 명령어에 대응하여 PC는 0x0 부터 4씩 증가하며 PC가 0xFFFF:FFFF일 때 프로그램이 종료된다.
- 각 사이클마다 아키텍쳐 상태의 변화가 생긴다면 user visible architectural state인 PC, GPR, Memory에 대한 상태를 출력해야 한다.
- 명령어가 전부 실행되면, 다음과 같은 값들을 출력해야합니다.
	- 최종 결과값 (R[2])
	- 총 사이클 횟수
	- 명령어 실행 횟수
	- R-type 명령어 실행 횟수
	- I-type 명령어 실행 횟수
	- J-type 명령어 실행 횟수
	- 메모리 액세스 명령어 실행 횟수
	- jump 횟수
	- taken branch 횟수
	- not-taken branch 횟수
	- 예측 성공한 branch 횟수 
	- 예측 실패한 branch 횟수

## Pipeline
- 명령어가 실행되는 동시에 다른 명령어들도 실행되는 병렬적인 구조를 구현해야 한다.
- 각 단계에서 발생한 명령어 대한 정보를 저장하는 공간인 latch를 구현해야 한다. latch는 한 사이클이 끝날 때 마다 다음 단계로 넘겨야 하며 각 단계에서 발생한 정보를 output, 각 단계로 들어가는 정보를 input으로 하는 총 4개의 latch를 구현해야 한다.
- 명령어들 끼리 생기는 dependency 중 data dependency와 control dependency를 해결할 수 있게 구현을 해야 한다. 

## Environment
- 사용 언어 : C
- 개발 환경 : Linux
- 파일 정보 : src/main.c src/fetch.c src/decode.c src/execute.c src/memory_access.c src/write_back.c src/MUX.c src/load.c src/pipeline.h

## How to Compile
1. git clone을 하여 소스파일이 모두 있는 디렉토리(src)에 위치한다.
2. gcc -Wall -Wextra -Werror *.c -o pipeline 를 입력하여 컴파일한다.
2-1) 옵션을 추가해준 이유는 모호한 코딩에 대한 경고와 모든 경고에 대해 컴파일 에러를 처리하여 더욱 완성도 있는 코드를 증명하기 위함이다.
3. 컴파일이 잘 되었다면 pipeline 실행 파일이 생성되었을 것이다. ./pipeline 원하는 input 디렉토리의 binary 파일명을 입력하여 실행한 후, 결과를 확인한다.

## Exception Handling
- input 파일을 불러오지 못하거나 빈 파일이라면 에러 메시지 출력 후 프로그램을 종료한다.
- 명령어를 decode 할 때, opcode가 정해진 format이 아니라면 에러 메시지 출력
![image](https://user-images.githubusercontent.com/70425484/124956708-3588d780-e053-11eb-90a9-b00ab4f4e6a3.png)
<br><br>
# MIPS Cache

## Description
 본 프로젝트는 캐시 메모리를 이용하여 더 효율적인 성능을 가진 MIPS 시뮬레이터를 구현하는 프로젝트이다. 이 프로그램은 input으로 들어온 실행 가능한 binary 파일의 각 명령어들을 해석하여 해당 소스코드의 결과와 동일한 결과를 얻는 것이 목표이다. 이 시뮬레이터에 포함된 ISA는 MIPS Green Sheet 의 CORE INSTRUCTION SET의 31개의 명령어 중 6개의 명령어(lbu, lhu, ll, sb, sc, sh)를 제외한 25개의 명령어이다. 각각의 명령어는 Single-Cycle MIPS를 따라 IF(Instruction Fetch), ID(Instruction Decode), EXE(EXEcution), MEM(MEMory access), WB(Write Back)의 다섯 단계를 거치는데, 이것은 실제 CPU와 동일하게 작동해야 한다. 캐시 메모리를 이용함으로써 파이프라인 혹은 싱글 사이클을 이용한 시뮬레이터 보다 메모리에 접근을 더 효율적이고 빠르게 할 수 있기 때문에 더 좋은 성능을 가진 시뮬레이터를 구현할 수 있다. 본 프로젝트를 통해 Direct-Mapped 캐시를 이해하고 캐시 사이즈에 따른 hit rate를 이용해 성능을 비교해보는 것이 목표이다.
 
## Requirements
- MIPS binary program(input 디렉토리의 .bin파일)을 input(실행 파일의 인자)으로 한다.
- 실제 CPU 동작과 동일하게 구현해야 한다.
  - 레지스터 : R[0] ~ R[31]까지 존재하며 LR(R[31])과 SP(R[29])를 제외한 모든 레지스터는 0으로 초기화되어야 한다. LR과 SP의 초기값은 각각 0xFFFF:FFFF, 0x100:0000이다.
  - 메모리 : 메모리는 16MB이다. 단, Instruction memory와 data memory를 하나의 메모리로 구현한다.
  - 캐시 메모리
  	- Direct Mapped Cache
  	- cache size : 256B
  	- cache line size : 64B
  	- Write Policy : write-back
  - PC : PC는 현재 명령어의 주소를 가지고 있는 레지스터로, 초기값은 프로그램의 시작주소인 0x0 이다. 각 명령어에 대응하여 PC는 0x0 부터 4씩 증가하며 PC가 0xFFFF:FFFF일 때 프로그램이 종료된다.
- 각 사이클마다 아키텍쳐 상태의 변화가 생긴다면 user visible architectural state인 PC, GPR, Memory에 대한 상태를 출력해야 한다.
- 명령어가 전부 실행되면, 다음과 같은 값들을 출력해야합니다.
	- 최종 결과값 (R[2])
	- 총 사이클 횟수
	- 명령어 실행 횟수
	- R-type 명령어 실행 횟수
	- I-type 명령어 실행 횟수
	- J-type 명령어 실행 횟수
	- 메모리 액세스 명령어 실행 횟수
	- jump 횟수
	- taken branch 횟수
	- not-taken branch 횟수
	- 예측 성공한 branch 횟수 
	- 예측 실패한 branch 횟수
	- 캐시에 접근한 횟수
	- 캐시 hit한 횟수
	- 캐시 miss한 횟수

## Cache
- Direct Mapped Cache<br>
![image](https://user-images.githubusercontent.com/70425484/125199396-ff409780-e2a0-11eb-9e88-c8f1835da72d.png)<br>
캐시와 메모리 간에 위 그림과 같이 mapping 되어 있는 것을 direct mapped cache 구조라고 한다. 캐시가 메모리의 특정 영역에 access 하고 싶으면 위와 같이 캐시의 한 영역이 여러 개의 memory로 공유된 형태를 띌 것이다.<br>
 address를 받으면 우선 tag, index, offset으로 나누어 쪼갠다. index와 offset에 해당하는 캐시가 valid라면 해당 캐시의 tag와 주소의 tag를 비교하여 일치하면 hit, 일치하지 않으면 miss이다. 간단하고 빠르지만, miss가 일어날 때 같은 index에서 tag가 달라 발생하는 conflict miss가 발생할 수 있다.
- Cache Miss : 위에서 설명한 것과 같이 tag값이 일치하지 않으면 miss 이다. 이때 miss의 종류는 다음과 같이 나눌 수 있다.
	- Cold Miss : 처음 캐시 메모리에 접근한다면 캐시 메모리는 초기화 상태로 모두 비어있다. 비어있는 캐시 메모리에 접근할 때는 무조건 miss가 나는데 이것을 cold miss라고 한다. 
	- Capacity Miss : 캐시 메모리의 용량이 부족하여 발생하는 miss로 접근하는 데이터의 양이 캐시의 사이즈를 넘어갈 경우 발생한다.
	- Conflict Miss : Direct mapped cache에서는 같은 index에 다른 tag가 들어왔을 때, set associative cache에서는 set에 way가 부족하여 발생하는 miss이다. 
- Write Policy : 데이터 변경 시 캐시 메모리와 메인 메모리에 데이터 저장 시점에 관한 정책이다.
	- Write Through : 캐시에 쓰기 명령이 이루어질 때 마다 캐시와 메모리에 동시에 데이터를 저장하는 정책이다. 항상 메모리에 접근하기 때문에 쓰기 명령에 걸리는 시간이 길어져 효율이 낮아진다. 
	- Write Back : 캐시에 쓰기 명령이 이루어지는 동안 캐시에만 내용을 저장하고 캐시의 내용이 제거될 때 메모리에 복사된다. 이때 dirty bit를 사용하여 잘못된 접근을 방지한다.
	- 
## Environment
- 사용 언어 : C
- 개발 환경 : Linux
- 파일 정보 : src/main.c src/fetch.c src/decode.c src/execute.c src/memory_access.c src/write_back.c src/MUX.c src/load.c src/DMcache.c src/pipeline.h

## How to Compile
1. git clone을 하여 소스파일이 모두 있는 디렉토리(src)에 위치한다.
2. gcc -Wall -Wextra -Werror *.c -o direct_mapped_cache 를 입력하여 컴파일한다.
2-1) 옵션을 추가해준 이유는 모호한 코딩에 대한 경고와 모든 경고에 대해 컴파일 에러를 처리하여 더욱 완성도 있는 코드를 증명하기 위함이다.
3. 컴파일이 잘 되었다면 direct_mapped_cache 실행 파일이 생성되었을 것이다. ./direct_mapped_cache 원하는 input 디렉토리의 binary 파일명을 입력하여 실행한 후, 결과를 확인한다.
