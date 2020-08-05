## 시스템 목표

26개의 도시(a ~ z)에 대하여 항공편에 대한 정보를 제공한다는 가정하에 최단 거리 알고리즘을 이용하여 도시 간의 최단 거리를 기반으로 최적의 항공편 예약 기능을 제공하는 것을 목표로 한다. 또한, 효율적인 데이터 저장을 위해 Red-Black Tree를 이용하여 예약 정보를 저장하여 시스템의 효율을 증가하는 것을 목표로 한다.

## 사용 가능한 기능

- <strong>항공 예약</strong>  
이름(cnt.name),출발지(cnt.source), 도착지(cnt.destination), 출발 날짜(cnt.sdate), 출발 시간(timeString) 좌석 선택을 입력하는 칸으로 넘어간다.
좌석 선택은 총 3가지를 할 수 있는데 총 3 종류(prestige, business, economy)를 사용자가 입력할 수 있다.
입력을 마치고 나면 출발 시간과 비행 시간에 따른 도착시간이 계산되고, 좌석에 따른 가격이 표시된다. 그리고 -1을 입력하면 메뉴로 돌아간다.
다음 그림은 항공 예약 흐름도다.

![img1](https://user-images.githubusercontent.com/15210906/89439547-51219900-d785-11ea-95c3-a3c949b46be3.png)

- <strong>항공 예약 취소</strong>  
항공 예약 취소는 항공 예약번호 입력을 통해서 이루어진다. 사용자가 예약번호를 입력하면 그 예약번호에 해당하는 정보가 지워지고 예약이 취소되었다는 문구가 뜬다.

- <strong>항공 조회</strong>  
항공 조회는 항공 예약번호 입력을 통해 이루어진다. 사용자가 예약번호를 입력하면 그 예약 번호에 해당하는 항공편 정보가 표시된다.


## UI

해당 시스템은 메뉴화면(MenuPage), 예약화면(ReservationPage), 예약취소화면(ReservationCanclePage),항공편선택(FlightListPage),좌석 선택(SeatInfoPage), 예약완료(ReservationCompletedPage), 예약 조회와 같이 총 6개의 페이지로 구성되어있다. 

- <strong>메뉴 화면</strong>  
  
![ui1](https://user-images.githubusercontent.com/15210906/89439612-68f91d00-d785-11ea-90e6-5ac8179efad2.jpg)  
  
- <strong>항공편 조회</strong>  
  
![ui2](https://user-images.githubusercontent.com/15210906/89439623-6d253a80-d785-11ea-9262-21972601871a.png)  
  
- <strong>항공편 선택</strong>  
  
![ui3](https://user-images.githubusercontent.com/15210906/89439626-6dbdd100-d785-11ea-806f-6f651f90cfb9.jpg)  
  
- <strong>좌석 선택</strong>  
  
![ui4](https://user-images.githubusercontent.com/15210906/89439628-6e566780-d785-11ea-876f-5d47a43f918a.jpg)  
  
- <strong>예약 완료</strong>  
  
![ui5](https://user-images.githubusercontent.com/15210906/89439630-6e566780-d785-11ea-94c6-751c7442eb01.jpg)  
  
