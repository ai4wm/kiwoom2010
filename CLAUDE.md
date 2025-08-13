# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

키움증권 OpenAPI 테스트 애플리케이션 - Visual Studio 2010으로 개발된 MFC 기반의 주식거래 시스템입니다. 키움증권의 ActiveX 컨트롤을 통해 실시간 시세 조회, 주문, 관심종목 관리 등의 기능을 제공합니다.

## Build Commands

### Visual Studio IDE
- 솔루션 파일: `KhOpenApiTest.sln`
- 프로젝트 파일: `KhOpenApiTest.vcxproj`
- 빌드 구성: Debug (동적 MFC 링킹), Release (정적 MFC 링킹)

### Command Line Build
```bash
# Visual Studio 2010 환경에서
devenv KhOpenApiTest.sln /build Debug
devenv KhOpenApiTest.sln /build Release

# 또는 MSBuild 사용
msbuild KhOpenApiTest.sln /p:Configuration=Debug /p:Platform=Win32
msbuild KhOpenApiTest.sln /p:Configuration=Release /p:Platform=Win32
```

### Important Build Settings
- **관리자 권한 필요**: UAC 실행 레벨이 RequireAdministrator로 설정됨
- **한국어 리소스**: Culture 0x0412 (한국어) 설정
- **Unicode**: MultiByte 문자셋 사용
- **MFC**: Debug는 동적 링킹, Release는 정적 링킹

## Architecture Overview

### Core Components

1. **메인 애플리케이션**
   - `CKhOpenApiTestApp`: 애플리케이션 클래스, 전역 OpenAPI 인스턴스 관리
   - `CKhOpenApiTestDlg`: 메인 다이얼로그, 화면 관리 및 이벤트 라우팅

2. **OpenAPI 래퍼 클래스**
   - `CKHOpenAPI`: 키움증권 ActiveX 컨트롤 래퍼 클래스
   - `CKHOpenAPICtrl`: 동일한 기능의 다른 래퍼 (중복)
   - CLSID: `{A1574A0D-6BFA-4BD7-9020-DED887118​18D}`

3. **기능별 다이얼로그**
   - `CCurrentPriceDlg`: 현재가 조회 (시세, 호가, 체결 데이터)
   - `COrderDlg`: 주문 처리 다이얼로그
   - `CKwanSimDlg`: 관심종목 관리
   - `CRealAddDlg`: 실시간 데이터 등록/해제
   - `CRateDlg`: 환율 정보

4. **그리드 컨트롤**
   - `CGridCtrl`: Chris Maunder의 MFC Grid Control v2.20+ 사용
   - 데이터 표시용 그리드 (현재가, 호가, 체결 등)

### Data Flow Architecture

1. **이벤트 기반 구조**
   ```
   키움 OpenAPI ActiveX → 이벤트 핸들러 → 화면별 처리 → 그리드 업데이트
   ```

2. **주요 이벤트 처리**
   - `OnReceiveTrDataKhopenapictrl`: TR 데이터 수신
   - `OnReceiveRealDataKhopenapictrl`: 실시간 데이터 수신
   - `OnReceiveMsgKhopenapictrl`: 메시지 수신
   - `OnReceiveChejanData`: 주문 체결 데이터 수신

3. **화면 번호 관리**
   - `m_mapScreen`: 화면 객체 맵핑
   - `m_mapScreenNum`: 화면 번호 관리
   - 각 화면마다 고유 번호 할당 (최대 100개)

### Key Design Patterns

1. **화면 관리 패턴**
   - 메인 다이얼로그에서 자식 다이얼로그 생성/관리
   - 화면 번호 기반 라우팅
   - 이벤트 싱크 맵을 통한 콜백 처리

2. **데이터 처리 패턴**
   - TR 코드 기반 데이터 요청 (OPT10001, OPT10003 등)
   - 실시간 데이터는 FID 기반 파싱
   - 그리드 컨트롤을 통한 데이터 표시

3. **에러 처리**
   - OpenAPI 에러 코드 체크 (`IsError` 함수)
   - 정의된 에러 코드 상수 사용
   - 시세/주문 관련 세분화된 에러 처리

## Development Guidelines

### File Structure
- `*.h/*.cpp`: 각 다이얼로그별 헤더/소스 파일
- `GridCtrl/`: 써드파티 그리드 컨트롤 라이브러리
- `res/`: 리소스 파일 (아이콘, 문자열 등)
- `Debug/Release/`: 빌드 출력 디렉토리

### 코딩 패턴
- Hungarian notation 사용 (m_, str, n 등)
- MFC 패턴 따름 (AFX, DDX/DDV)
- 한글 주석과 변수명 혼용

### 중요 고려사항
- **ActiveX 의존성**: 키움 OpenAPI ActiveX가 시스템에 설치되어야 함
- **관리자 권한**: 프로그램 실행 시 관리자 권한 필요
- **실시간 데이터**: 이벤트 기반 비동기 처리
- **화면 번호 제한**: 최대 100개 화면 동시 사용 가능

### TR 코드 정의
```cpp
#define TR_OPT10001 "OPT10001"  // 주식기본정보
#define TR_OPT10003 "OPT10003"  // 체결정보
#define TR_OPT10004 "OPT10004"  // 주식호가
#define TR_OPT10080 "OPT10080"  // 주식분봉조회
#define TR_OPT10081 "OPT10081"  // 주식일봉조회
```

### 데이터 타입 정의
```cpp
#define DT_NONE         0  // 기본포맷
#define DT_DATE         1  // 날짜 포맷
#define DT_TIME         2  // 시간 포맷  
#define DT_NUMBER       3  // 숫자 포맷
#define DT_ZERO_NUMBER  4  // 숫자(0표시) 포맷
#define DT_SIGN         5  // 부호 포맷
```