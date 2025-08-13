# 키움증권 OpenAPI 테스트 애플리케이션

키움증권 OpenAPI를 활용한 MFC 기반 주식 거래 시스템 테스트 애플리케이션입니다.

## 📋 주요 기능

- **실시간 시세 조회**: 주식 현재가, 호가, 체결 정보 실시간 조회
- **주문 처리**: 매수/매도 주문 기능
- **관심종목 관리**: 관심종목 등록 및 관리
- **환율 정보**: 실시간 환율 정보 조회
- **실시간 데이터**: 실시간 시세 등록/해제 기능

## 🛠 개발 환경

- **IDE**: Visual Studio 2010
- **프레임워크**: MFC (Microsoft Foundation Classes)
- **언어**: C++
- **플랫폼**: Windows 32bit
- **외부 의존성**: 키움증권 OpenAPI ActiveX 컨트롤

## 🚀 빌드 및 실행

### 사전 요구사항
1. Visual Studio 2010 이상
2. 키움증권 OpenAPI 설치 ([키움증권 홈페이지](https://www.kiwoom.com)에서 다운로드)
3. Windows 관리자 권한

### 빌드 방법

#### Visual Studio IDE 사용
```bash
1. KhOpenApiTest.sln 파일을 Visual Studio로 열기
2. 빌드 구성 선택 (Debug/Release)
3. F7 키 또는 빌드 메뉴에서 솔루션 빌드
```

#### 명령줄 빌드
```bash
# Visual Studio 2010 환경에서
devenv KhOpenApiTest.sln /build Debug
devenv KhOpenApiTest.sln /build Release

# MSBuild 사용
msbuild KhOpenApiTest.sln /p:Configuration=Debug /p:Platform=Win32
msbuild KhOpenApiTest.sln /p:Configuration=Release /p:Platform=Win32
```

### 실행
- 빌드 완료 후 `Debug/KhOpenApiTest.exe` 또는 `Release/KhOpenApiTest.exe` 실행
- **주의**: 관리자 권한으로 실행 필요

## 📁 프로젝트 구조

```
├── KhOpenApiTest.sln          # 솔루션 파일
├── KhOpenApiTest.vcxproj      # 프로젝트 파일
├── KhOpenApiTest.h/.cpp       # 메인 애플리케이션
├── KhOpenApiTestDlg.h/.cpp    # 메인 다이얼로그
├── KHOpenAPI.h/.cpp           # OpenAPI 래퍼 클래스
├── CurrentPriceDlg.h/.cpp     # 현재가 조회 다이얼로그
├── OrderDlg.h/.cpp            # 주문 다이얼로그
├── KwanSimDlg.h/.cpp          # 관심종목 다이얼로그
├── RealAddDlg.h/.cpp          # 실시간 데이터 다이얼로그
├── RateDlg.h/.cpp             # 환율 다이얼로그
├── GridCtrl/                  # 그리드 컨트롤 라이브러리
├── res/                       # 리소스 파일
├── Debug/                     # 디버그 빌드 출력
└── Release/                   # 릴리스 빌드 출력
```

## 🔧 기술 세부사항

### 핵심 컴포넌트

1. **OpenAPI 연동**
   - ActiveX 컨트롤 기반 (CLSID: {A1574A0D-6BFA-4BD7-9020-DED887118​18D})
   - 이벤트 기반 비동기 처리
   - TR 코드를 통한 데이터 요청/응답

2. **데이터 표시**
   - Chris Maunder의 MFC Grid Control v2.20+ 사용
   - 실시간 데이터 업데이트 지원
   - 다양한 데이터 포맷 지원 (날짜, 시간, 숫자, 부호)

3. **화면 관리**
   - 화면 번호 기반 라우팅 (최대 100개)
   - 이벤트 싱크 맵을 통한 콜백 처리
   - 모달/모덜리스 다이얼로그 혼용

### 주요 TR 코드
- `OPT10001`: 주식기본정보
- `OPT10003`: 체결정보  
- `OPT10004`: 주식호가
- `OPT10080`: 주식분봉조회
- `OPT10081`: 주식일봉조회

## ⚠️ 주의사항

1. **키움증권 계좌 필요**: 실제 거래를 위해서는 키움증권 계좌가 필요합니다
2. **API 인증**: 키움증권 OpenAPI 사용을 위한 별도 인증 절차가 필요할 수 있습니다
3. **관리자 권한**: 애플리케이션 실행 시 Windows 관리자 권한이 필요합니다
4. **ActiveX 의존성**: 키움증권 OpenAPI ActiveX가 시스템에 설치되어야 합니다

## 📄 라이선스

이 프로젝트는 키움증권 OpenAPI 테스트 목적으로 제작되었습니다.
- 키움증권 OpenAPI 사용 조건을 준수해야 합니다
- 상업적 사용 시 별도 라이선스 검토가 필요합니다

## 🤝 기여 방법

1. 이 저장소를 포크합니다
2. 새로운 기능 브랜치를 생성합니다 (`git checkout -b feature/새기능`)
3. 변경사항을 커밋합니다 (`git commit -am '새 기능 추가'`)
4. 브랜치에 푸시합니다 (`git push origin feature/새기능`)
5. Pull Request를 생성합니다

## 📞 지원

- 키움증권 OpenAPI 관련 문의: [키움증권 고객센터](https://www.kiwoom.com)
- 프로젝트 관련 이슈: GitHub Issues를 통해 문의

---

**Version**: 2.7  
**Last Updated**: 2014-2015  
**Copyright**: (주)한국투자치