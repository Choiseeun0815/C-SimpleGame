# C-SimpleGame
비주얼 스튜디오 c++의 콘솔창을 활용한 간단한 게임.  

## 게임 룰(Human의 Food 먹기 게임)
게임에는 Human, Monster, Food의 세 객체가 등장하며 이들은 10x20 격자판에서 각각 정해진 규칙에 의해 움직인다.

Human 객체는 사용자의 키에 의해 좌(a키), 하(s키), 상(d키), 우(f키)로 한 칸씩 움직이고,

Monster는 한 번에 2칸씩 좌,하,상,우 방향으로 랜덤하게 움직인다.

Food는 5번 중에 3번은 제자리에 있으며, 나머지 2번은 4가지 방향 중 랜덤하게 한 칸씩 움직인다.

게임은 Human이 Monster를 피해 Food를 먹으면(Food의 위치로 이동) 성공으로 끝나고,

Monster가 Food를 먹거나 Human이 Monster에게 잡히면 실패로 끝난다. 

임의로 Human, Monster, Food를 나타내는 기호를 각각 H, M, @로 표현한다. 

# 실행시 화면
![image](https://github.com/Choiseeun0815/Calendar/assets/103297048/a777ed10-686a-4381-aa80-70ef327e47b3)

# 수행 영상 
https://github.com/Choiseeun0815/Calendar/assets/103297048/27467c38-ef8a-41e4-a0a7-b656fea02118
