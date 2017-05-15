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
	// 2. ����һ��face
	error = FT_New_Face(library, "Assets\\font\\msyh.ttc", 0, &face);
}

void Font::SetFontSize(int size)
{
	// 3. ��������ߴ�
	error = FT_Set_Char_Size(face, size * 64, size * 64, 96, 96);
}

TexturePtr Font::GetStrTexture(string str)
{
	// 4. ��ȡ�ַ�ͼ������
	Uint32 charIdx = FT_Get_Char_Index(face, L'��');

	// 5. �����ַ�ͼ��
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
	//ת����λͼ  
	FT_Render_Glyph(face->glyph, FT_RENDER_MODE_LCD);//FT_RENDER_MODE_NORMAL  );   
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//ȡ��λͼ����  
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	//��λͼ���ݿ����Լ��������������.�����ɿ��Ի�����Ҫ�Ķ��������ˡ�  
	int width = bitmap.width;
	int height = bitmap.rows;

	m_FT_Face->size->metrics.y_ppem;      //�������뵽�豸�ռ�  
	m_FT_Face->glyph->metrics.horiAdvance;  //ˮƽ�ı�����  


	charTex.m_Width = width;
	charTex.m_Height = height;
	charTex.m_adv_x = m_FT_Face->glyph->advance.x / 64.0f;  //�������  
	charTex.m_adv_y = m_FT_Face->size->metrics.y_ppem;        //m_FT_Face->glyph->metrics.horiBearingY / 64.0f;  
	charTex.m_delta_x = (float)bitmap_glyph->left;           //left:����ԭ��(0,0)������λͼ��������ص�ˮƽ����.�����������ص���ʽ��ʾ��   
	charTex.m_delta_y = (float)bitmap_glyph->top - height;   //Top: ���������β۵�bitmap_top�ֶΡ�  
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);  //ָ��һ����ά������ͼƬ  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);                            //glTexParameteri():�������  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);                                //������л��  

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
