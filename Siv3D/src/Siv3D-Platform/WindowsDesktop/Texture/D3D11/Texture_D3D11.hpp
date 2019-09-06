﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Windows.hpp>
# include <d3d11.h>
# include <Siv3D/PointVector.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Array.hpp>
# include <Siv3D/Texture.hpp>
# include <Siv3D/TextureFormat.hpp>
# include "Texture2DDesc_D3D11.hpp"

namespace s3d
{
	class Texture_D3D11
	{
	private:

		// [メインテクスチャ]
		ComPtr<ID3D11Texture2D> m_texture;

		// [ステージング・テクスチャ]
		ComPtr<ID3D11Texture2D> m_stagingTexture;

		// [シェーダ・リソース・ビュー]
		ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

		// [レンダー・ターゲット・ビュー]
		ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		enum class TextureType
		{
			// 通常テクスチャ
			Normal,

			// 動的テクスチャ
			Dynamic,

			// レンダーテクスチャ
			Render,
		};

		Texture2DDesc_D3D11 m_desc;

		TextureType m_type = TextureType::Normal;

		bool m_initialized = false;

	public:

		struct Dynamic {};
		struct Render {};

		Texture_D3D11(Dynamic, ID3D11Device* device, const Size& size, const void* pData, uint32 stride, TextureFormat format, TextureDesc desc);

		Texture_D3D11(Render, ID3D11Device* device, const Size& size, TextureFormat format, TextureDesc desc);

		Texture_D3D11(Render, ID3D11Device* device, const Image& image, TextureFormat format, TextureDesc desc);

		Texture_D3D11(ID3D11Device* device, const Image& image, TextureDesc desc);

		Texture_D3D11(ID3D11Device* device, const Image& image, const Array<Image>& mips, TextureDesc desc);

		bool isInitialized() const noexcept;

		const Texture2DDesc_D3D11& getDesc() const noexcept;

		ID3D11ShaderResourceView** getSRVPtr();

		ID3D11Texture2D* getTexture();

		ID3D11RenderTargetView* getRTV();

		// レンダーテクスチャを指定した色でクリアする
		void clearRT(ID3D11DeviceContext* context, const ColorF& color);

		// レンダーテクスチャの内容を Image にコピーする
		void readRT(ID3D11Device* device, ID3D11DeviceContext* context, Image& image);

		// 動的テクスチャを指定した色で塗りつぶす
		bool fill(ID3D11DeviceContext* context, const ColorF& color, bool wait);

		bool fillRegion(ID3D11DeviceContext* context, const ColorF& color, const Rect& rect);

		bool fill(ID3D11DeviceContext* context, const void* src, uint32 stride, bool wait);

		bool fillRegion(ID3D11DeviceContext* context, const void* src, uint32 stride, const Rect& rect, bool wait);
	};
}