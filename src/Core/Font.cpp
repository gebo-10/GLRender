#include <Font.h>
Font::Font()
{

}

Font::~Font()
{

}

bool Font::Init()
{
	error = FT_Init_FreeType(&library);
	return true;
}

void Font::SetFont(const char* font_file)
{
	// 2. 创建一个face
	error = FT_New_Face(library, "Assets\\font\\msyh.ttc", 0, &face);
}

void Font::SetFontSize(int size)
{
	// 3. 设置字体尺寸
	error = FT_Set_Char_Size(face, size * 64, size * 64, 96, 96);
}

TexturePtr Font::GetStrTexture(string str)
{
	// 4. 获取字符图像索引
	Uint32 charIdx = FT_Get_Char_Index(face, L'我');

	// 5. 加载字符图像
	FT_Load_Glyph(face, charIdx, FT_LOAD_DEFAULT);

	TexturePtr ptr = make_shared<Texture>();
	int width = 100;
	int height = 100;
	Color * tmp = new Color[width *height];
	for (int i=0;i<height;i++)
	{
		for (int j=0;j<width;j++)
		{
			int index = i*width + j;
			tmp[index].r = i;
			tmp[index].g = j;
			tmp[index].b = 100;
			tmp[index].a = 255;
		}
	}
	//ptr->InitFromMem( (void * )tmp, width,  height);

	FT_Glyph glyph;
	FT_Get_Glyph(face->glyph, &glyph);

	//Convert the glyph to a bitmap.
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//This reference will make accessing the bitmap easier
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	char* pBuf = new char[width * height * 4];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
			pBuf[(4 * i + (height - j - 1) * width * 4)] = _vl;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = 0xFF;
		}
	}

	ptr->InitFromMem((void *)pBuf, width, width);
/*
	//转化成位图  
	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  );   
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//取道位图数据  
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//把位图数据拷贝自己定义的数据区里.这样旧可以画到需要的东西上面了。  
	int width = bitmap.width;
	int height = bitmap.rows;

	m_FT_Face->size->metrics.y_ppem;      //伸缩距离到设备空间  
	m_FT_Face->glyph->metrics.horiAdvance;  //水平文本排列  


	charTex.m_Width = width;
	charTex.m_Height = height;
	charTex.m_adv_x = m_FT_Face->glyph->advance.x / 64.0f;  //步进宽度  
	charTex.m_adv_y = m_FT_Face->size->metrics.y_ppem;        //m_FT_Face->glyph->metrics.horiBearingY / 64.0f;  
	charTex.m_delta_x = (float)bitmap_glyph->left;           //left:字形原点(0,0)到字形位图最左边象素的水平距离.它以整数象素的形式表示。   
	charTex.m_delta_y = (float)bitmap_glyph->top - height;   //Top: 类似于字形槽的bitmap_top字段。  
	glGenTextures(1, &charTex.m_texID);
	glBindTexture(GL_TEXTURE_2D, charTex.m_texID);
	char* pBuf = new char[width * height * 4];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
			pBuf[(4 * i + (height - j - 1) * width * 4)] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = _vl;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //指定一个二维的纹理图片  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);                            //glTexParameteri():纹理过滤  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);                                //纹理进行混合  

	/*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);*
	delete[] pBuf;


	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_ALPHA, GL_UNSIGNED_BYTE, bitmap.buffer);
	ptr->
*/
	return ptr;
}
