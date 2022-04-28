#pragma once

//function for customer menu
void customer(); // 고객 관련 메뉴
void cust_search(); // 고객 찾기
void search_cid(); // 고객 아이디로 찾기
void search_cname(); // 고객 이름으로 찾기
void cust_entry(); // 고객 추가
void cust_list(); // 고객 리스트 보기
void cust_update(); // 고객 정보 업데이트


//function for auto increment customer id
int getcust_id(); // 고객 아이디 입력받기 함수