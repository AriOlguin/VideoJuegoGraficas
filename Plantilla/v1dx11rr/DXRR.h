#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"



class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;

	int frameBillboard;

	TerrenoRR *terreno;
	SkyDome *skydome;
	BillboardRR *billboard;
	Camara *camara;
	ModeloRR* model;
	//PUEBLO 01
	ModeloRR* iglesia, * pozo, * columpios;
	//PUEBLO 02
	ModeloRR* casa, * casa01, * casa02, * molino;
	//GRANJA
	ModeloRR* caba�a, * caba�a2, * granero , * corral;
	//MOBS  
	ModeloRR *toro, * caballo, * dog;
	//ITEMS
	ModeloRR * bidon, * bolsa, * generador, *faro ;
	//PUEBLO 03
	ModeloRR* casa03, * casa04, * casa05, * casa06,*casa07,*casa08;
	//MOBS Hostiles

	//OTROS
	ModeloRR* llanta,*carro,*tractor;

	float izqder;
	float arriaba;
	float vel;
	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;
	
    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		billCargaFuego();
		camara = new Camara(D3DXVECTOR3(0,80,6), D3DXVECTOR3(0,80,0), D3DXVECTOR3(0,1,0), Ancho, Alto);
		terreno = new TerrenoRR(1024, 1024, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"SkyDome.png");
		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png",L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
		model = new ModeloRR(d3dDevice, d3dContext, "Assets/Cofre/Cofre.obj", L"Assets/Cofre/Cofre-color.png", L"Assets/Cofre/Cofre-spec.png", 0, 0);
		
		//casa = new ModeloRR(d3dDevice, d3dContext, "modelos/cabana/cottage_fbx.obj", L"modelos/cabana/cottage_diffuse.png", L"modelos/cabana/cottage_specular.png", 40, 0); 
		
		
		//Items
		faro = new ModeloRR(d3dDevice, d3dContext, "modelos/Faro/Faro.obj", L"modelos/Faro/1001_albedo.jpg", L"modelos/Bidon/low_default_Roughness.png", -20, 0);
		bidon = new ModeloRR(d3dDevice, d3dContext, "modelos/Bidon/Bidon.obj", L"modelos/Bidon/low_default_BaseColor.png", L"modelos/Bidon/low_default_Roughness.png", 0, 0);
		bolsa = new ModeloRR(d3dDevice, d3dContext, "modelos/Bolsa/Bolsa.obj", L"modelos/Bolsa/PlasticBag_Albedo.jpg", L"modelos/Bolsa/PlasticBag_roughness.jpg", 20, 0);
		generador = new ModeloRR(d3dDevice, d3dContext, "modelos/Generador/Generador.obj", L"modelos/Generador/DieselGenerator_BC.png", L"modelos/Generador/DieselGenerator_R.png", 40, 0);
		
		//Mobs
		caballo = new ModeloRR(d3dDevice, d3dContext, "modelos/Caballo/horse2.obj", L"modelos/Caballo/Horse2.jpg", L"modelos/iglesia/gethsemane_specular.png", 0, 350);
		toro = new ModeloRR(d3dDevice, d3dContext, "modelos/Toro/Toro.obj", L"modelos/Toro/Bull texture.png", L"modelos/Toro/Bull textureS.png", 60, 350);
		dog = new ModeloRR(d3dDevice, d3dContext, "modelos/PerroEvil/EvilDog.obj", L"modelos/PerroEvil/dog.png", L"modelos/Generador/DieselGenerator_R.png", 120, 350);
		
		//Granja
		caba�a = new ModeloRR(d3dDevice, d3dContext, "modelos/cabana/cottage_fbx.obj", L"modelos/cabana/cottage_diffuse.png", L"modelos/cabana/cottage_specular.png", -50, 450);
		granero = new ModeloRR(d3dDevice, d3dContext, "modelos/Granero/Granero.obj", L"modelos/Granero/barn_BaseColor.png", L"modelos/Granero/barn_Roughness.png", 0, 450);
		corral = new ModeloRR(d3dDevice, d3dContext, "modelos/Corral 3/corral3.obj", L"modelos/Corral 3/corral2.jpg", L"modelos/cabana/cottage_specular.png", -100, 350);
		caba�a2 = new ModeloRR(d3dDevice, d3dContext, "modelos/cabana/cottage_fbx.obj", L"modelos/cabana/cottage_diffuse.png", L"modelos/cabana/cottage_specular.png", -100, 450);
		//Pueblo 01
		molino = new ModeloRR(d3dDevice, d3dContext, "modelos/molino2/molino2.obj", L"modelos/molino2/molino2.jpg", L"modelos/molino2/molino2S.jpg", -300, -350);
		casa01 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 1/Casa1.obj", L"modelos/Casa 1/diff.png", L"modelos/cabana/cottage_specular.png", -350, -350);
		casa02 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 2/Casa 2.obj", L"modelos/Casa 2/House3_BaseColor.png", L"modelos/cabana/cottage_specular.png", -250, -300);
	

		//Pueblo 02
		columpios = new ModeloRR(d3dDevice, d3dContext, "modelos/Columpios/juegosParque.obj", L"modelos/Columpios/1001_albedo.jpg", L"modelos/Columpios/specular.jpg", 200, 400);
		iglesia = new ModeloRR(d3dDevice, d3dContext, "modelos/iglesia/iglesia.obj", L"modelos/iglesia/gethsemane_diffuse.png", L"modelos/iglesia/gethsemane_specular.png", 150, 380);
		pozo = new ModeloRR(d3dDevice, d3dContext, "modelos/Pozo/Pozo1.obj", L"modelos/pozo/waterwellcolor.png", L"modelos/cabana/cottage_specular.png", 200, 360);

		//PUEBLO 03
		casa03 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 1/Casa1.obj", L"modelos/Casa 1/diff.png", L"modelos/cabana/cottage_specular.png", 0, 300);
		casa04 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 2/Casa 2.obj", L"modelos/Casa 2/House3_BaseColor.png", L"modelos/cabana/cottage_specular.png", -50, 300);
		casa05 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 1/Casa1.obj", L"modelos/Casa 1/diff.png", L"modelos/cabana/cottage_specular.png", -50, 100);
		casa06 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 2/Casa 2.obj", L"modelos/Casa 2/House3_BaseColor.png", L"modelos/cabana/cottage_specular.png", 0, 100);
		casa07 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 2/Casa 2.obj", L"modelos/Casa 2/House3_BaseColor.png", L"modelos/cabana/cottage_specular.png", 50, 300);
		casa08 = new ModeloRR(d3dDevice, d3dContext, "modelos/Casa 1/Casa1.obj", L"modelos/Casa 1/diff.png", L"modelos/cabana/cottage_specular.png", 50, 100);

		//OTROS

		llanta = new ModeloRR(d3dDevice, d3dContext, "modelos/Llantas/Llanta.obj", L"modelos/Llantas/Tire01_low_1001_BaseColor.png", L"modelos/Generador/DieselGenerator_R.png", 60, 0);
		carro = new ModeloRR(d3dDevice, d3dContext, "modelos/Carro/Carro.obj", L"modelos/Carro/car_d.png", L"modelos/Generador/DieselGenerator_R.png", 100, 0);
		tractor = new ModeloRR(d3dDevice, d3dContext, "modelos/Tractor/Tractor.obj", L"modelos/Tractor/foto2.jpg", L"modelos/Generador/DieselGenerator_R.png", 140, 0);

		
	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		return true;			
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}
	
	void Render(void)
	{
		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if( d3dContext == 0 )
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView( backBufferTarget, clearColor );
		d3dContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 5 ;
		camara->UpdateCam(vel, arriaba, izqder);
		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);
		//TurnOnAlphaBlending();
		billboard->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5, uv1, uv2, uv3, uv4, frameBillboard);

		//TurnOffAlphaBlending();

		//GRANJA
	    //model->Draw(camara, terreno->Superficie(100, 20), 10.0f, 0, 'A', 1);
		caba�a->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.01);
		caba�a2->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.01);
		corral->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.8);
		granero->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 30);

		//PUEBLO PARTE 1
		casa01->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 3.0);
		casa02->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.035);
		molino->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 1);

		//PUEBLO PARTE 2
		iglesia->Draw(camara, terreno->Superficie(0, 0), 2.0f, 0, 'A', 0.02);
		pozo->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 5);	
		columpios->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 5);
		

		//MOBS
		toro->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 1);
		caballo->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 1);
		dog->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.05);

		//ITEMS
		faro->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 1.00);
		bidon->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 15);
		bolsa->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.03);
		generador->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 4);
		
		//PUEBLO03
		casa03->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 3.0);
		casa04->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.035);
		casa05->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 3.0);
		casa06->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.035);
		casa07->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.035);
		casa08->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 3.0);
		
		//Llanta
		llanta->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 50);
		carro->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 1);
		tractor->Draw(camara, terreno->Superficie(0, 0), 25.0f, 0, 'A', 0.005);
		swapChain->Present( 1, 0 );

		
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2])
			collition = true;
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif