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
