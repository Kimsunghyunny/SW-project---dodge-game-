# 2018-1-OSSP-OILSAO-9
2018-1-OSSP-오일사오-9

## README

- 기존 오픈소스 : https://github.com/khodzha/square-dodge
- 1차 수정 소스 : https://github.com/CSID-DGU/2017-2-OSSP-Awesome-1


## 라인 수 및 파일 개수

- 기존 라인 수 : 약 1300줄, 확장된 라인 수 : 약 800줄
- game_state.cpp에 함수를 추가하는 방식으로 소스코드 확장

## 멀티모드 실행 시 유의사항

- game_state.h에 ip를 각 PC의 ip로 넣어서 make 해야 듀얼 플레이 가능
- 가상 머신으로 돌릴 경우 가상 머신의 ip를 넣어야 함



## How to run

1. 리눅스 터미널을 실행
2. 닷지를 다운 받은 directory로 이동
3. MakeFile의 코드를 실행
4. 터미널에 ./main 입력


## 실행 시 유의사항

- 실행 시, mysql 설치 되어 있어야함
- 멀티모드 실행시, game_state.h에 ip를 각 PC의 ip로 넣어서 make 해야 듀얼 플레이 가능 / 가상 머신으로 돌릴 경우 가상 머신의 ip를 넣어야 함

## 동영상

- 기존 소스 프로그램 영상 : https://youtu.be/ZOq-FuQx2Zg
- 1차 확장 소스 프로그램 영상 : https://youtu.be/ufeNuZz0AFw
- OILSAO 확장 소스 프로그램 영상 : 
