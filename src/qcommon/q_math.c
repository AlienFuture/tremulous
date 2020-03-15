/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2000-2013 Darklegion Development
Copyright (C) 2015-2019 GrangerHub

This file is part of Tremulous.

Tremulous is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 3 of the License,
or (at your option) any later version.

Tremulous is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tremulous; if not, see <https://www.gnu.org/licenses/>

===========================================================================
*/
//
// q_math.c -- stateless support routines that are included in each code module

// Some of the vector functions are static inline in q_shared.h. q3asm
// doesn't understand static functions though, so we only want them in
// one file. That's what this is about.
#ifdef Q3_VM
#define __Q3_VM_MATH
#endif

#include "q_shared.h"

vec3_t	vec3_origin = {0,0,0};
vec3_t	axisDefault[3] = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };


vec4_t		colorBlack	= {0.000f, 0.000f, 0.000f, 1.000f};
vec4_t		colorRed	= {1.000f, 0.000f, 0.000f, 1.000f};
vec4_t		colorGreen	= {0.000f, 1.000f, 0.000f, 1.000f};
vec4_t		colorBlue	= {0.000f, 0.000f, 1.000f, 1.000f};
vec4_t		colorYellow	= {1.000f, 1.000f, 0.000f, 1.000f};
vec4_t		colorMagenta	= {1.000f, 0.000f, 1.000f, 1.000f};
vec4_t		colorCyan	= {0.000f, 1.000f, 1.000f, 1.000f};
vec4_t		colorWhite	= {1.000f, 1.000f, 1.000f, 1.000f};
vec4_t		colorGray = {0.502f, 0.502f, 0.502f, 1.000f};
vec4_t		colorOrange = {1.000f, 0.686f, 0.000f, 1.000f};
vec4_t		colorRoseBud = {0.996f, 0.671f, 0.604f, 1.000f};
vec4_t		colorPaleGreen = {0.596f, 0.984f, 0.596f, 1.000f};
vec4_t		colorPaleGolden = {0.933f, 0.910f, 0.667f, 1.000f};
vec4_t		colorColumbiaBlue = {0.608f, 0.867f, 1.000f, 1.000f};
vec4_t		colorPaleTurquoise = {0.686f, 0.933f, 0.933f, 1.000f};
vec4_t		colorPaleVioletRed = {0.859f, 0.439f, 0.576f, 1.000f};
vec4_t		colorPalacePaleWhite = {0.910f, 0.898f, 0.863f, 1.000f};
vec4_t		colorOlive = {0.231f, 0.235f, 0.212f, 1.000f};
vec4_t		colorTomato = {1.000f, 0.388f, 0.278f, 1.000f};
vec4_t		colorLime = {0.749f, 1.000f, 0.000f, 1.000f};
vec4_t		colorLemon = {1.000f, 0.969f, 0.000f, 1.000f};
vec4_t		colorBlueBerry = {0.310f, 0.525f, 0.969f, 1.000f};
vec4_t		colorTurquoise = {0.251f, 0.878f, 0.816f, 1.000f};
vec4_t		colorWildWatermelon = {0.992f, 0.357f, 0.471f, 1.000f};
vec4_t		colorSaltpan = {0.933f, 0.953f, 0.898f, 1.000f};
vec4_t		colorGrayChateau = {0.624f, 0.639f, 0.655f, 1.000f};
vec4_t		colorRust = {0.718f, 0.255f, 0.055f, 1.000f};
vec4_t		colorCopperGreen = {0.431f, 0.553f, 0.443f, 1.000f};
vec4_t		colorGold = {1.000f, 0.843f, 0.000f, 1.000f};
vec4_t		colorSteelBlue = {0.275f, 0.510f, 0.706f, 1.000f};
vec4_t		colorSteelGray = {0.482f, 0.565f, 0.584f, 1.000f};
vec4_t		colorBronze = {0.804f, 0.498f, 0.196f, 1.000f};
vec4_t		colorSilver = {0.753f, 0.753f, 0.753f, 1.000f};
vec4_t		colorDarkGray = {0.663f, 0.663f, 0.663f, 1.000f};
vec4_t		colorDarkOrange = {1.000f, 0.549f, 0.000f, 1.000f};
vec4_t		colorDarkGreen = {0.000f, 0.392f, 0.000f, 1.000f};
vec4_t		colorRedOrange = {1.000f, 0.247f, 0.204f, 1.000f};
vec4_t		colorForestGreen = {0.133f, 0.545f, 0.133f, 1.000f};
vec4_t		colorBrightSun = {0.926f, 0.741f, 0.173f, 1.000f};
vec4_t		colorMediumSlateBlue = {0.482f, 0.408f, 0.933f, 1.000f};
vec4_t		colorCeleste = {0.698f, 1.000f, 1.000f, 1.000f};
vec4_t		colorIronstone = {0.525f, 0.314f, 0.251f, 1.000f};
vec4_t		colorTimberwolf = {0.859f, 0.843f, 0.824f, 1.000f};
vec4_t		colorOnyx = {0.059f, 0.059f, 0.059f, 1.000f};
vec4_t		colorRosewood = {0.396f, 0.000f, 0.043f, 1.000f};
vec4_t		colorKokoda = {0.482f, 0.471f, 0.353f, 1.000f};
vec4_t		colorPorsche = {0.875f, 0.616f, 0.357f, 1.000f};
vec4_t		colorCloudBurst = {0.208f, 0.369f, 0.310f, 1.000f};
vec4_t		colorBlueDiane = {0.208f, 0.318f, 0.310f, 1.000f};
vec4_t		colorRope = {0.557f, 0.349f, 0.235f, 1.000f};
vec4_t		colorBlonde = {0.980f, 0.941f, 0.745f, 1.000f};
vec4_t		colorSmokeyBlack = {0.063f, 0.047f, 0.031f, 1.000f};
vec4_t		colorAmericanRose = {1.000f, 0.012f, 0.243f, 1.000f};
vec4_t		colorNeonGreen = {0.224f, 1.000f, 0.078f, 1.000f};
vec4_t		colorNeonYellow = {0.980f, 0.929f, 0.153f, 1.000f};
vec4_t		colorUltramarine = {0.071f, 0.039f, 0.561f, 1.000f};
vec4_t		colorTurquoiseBlue = {0.000f, 1.000f, 0.937f, 1.000f};
vec4_t		colorDarkMagenta = {0.545f, 0.000f, 0.545f, 1.000f};
vec4_t		colorMagicMint = {0.667f, 0.941f, 0.820f, 1.000f};
vec4_t		colorLightGray = {0.827f, 0.827f, 0.827f, 1.000f};
vec4_t		colorLightSalmon = {1.000f, 0.600f, 0.600f, 1.000f};
vec4_t		colorLightGreen = {0.565f, 0.933f, 0.565f, 1.000f};

vec4_t	g_color_table[62] =
	{
	{0.250f, 0.250f, 0.250f, 1.000f},
	{1.000f, 0.000f, 0.000f, 1.000f},
	{0.000f, 1.000f, 0.000f, 1.000f},
	{1.000f, 1.000f, 0.000f, 1.000f},
	{0.000f, 0.000f, 1.000f, 1.000f},
	{0.000f, 1.000f, 1.000f, 1.000f},
	{1.000f, 0.000f, 1.000f, 1.000f},
	{1.000f, 1.000f, 1.000f, 1.000f},
	{0.502f, 0.502f, 0.502f, 1.000f},
	{1.000f, 0.686f, 0.000f, 1.000f},
	{0.996f, 0.671f, 0.604f, 1.000f},
	{0.596f, 0.984f, 0.596f, 1.000f},
	{0.933f, 0.910f, 0.667f, 1.000f},
	{0.608f, 0.867f, 1.000f, 1.000f},
	{0.686f, 0.933f, 0.933f, 1.000f},
	{0.859f, 0.439f, 0.576f, 1.000f},
	{0.910f, 0.898f, 0.863f, 1.000f},
	{0.231f, 0.235f, 0.212f, 1.000f},
	{1.000f, 0.388f, 0.278f, 1.000f},
	{0.749f, 1.000f, 0.000f, 1.000f},
	{1.000f, 0.969f, 0.000f, 1.000f},
	{0.310f, 0.525f, 0.969f, 1.000f},
	{0.251f, 0.878f, 0.816f, 1.000f},
	{0.992f, 0.357f, 0.471f, 1.000f},
	{0.933f, 0.953f, 0.898f, 1.000f},
	{0.624f, 0.639f, 0.655f, 1.000f},
	{0.718f, 0.255f, 0.055f, 1.000f},
	{0.431f, 0.553f, 0.443f, 1.000f},
	{1.000f, 0.843f, 0.000f, 1.000f},
	{0.275f, 0.510f, 0.706f, 1.000f},
	{0.482f, 0.565f, 0.584f, 1.000f},
	{0.804f, 0.498f, 0.196f, 1.000f},
	{0.753f, 0.753f, 0.753f, 1.000f},
	{0.663f, 0.663f, 0.663f, 1.000f},
	{1.000f, 0.549f, 0.000f, 1.000f},
	{0.000f, 0.392f, 0.000f, 1.000f},
	{1.000f, 0.247f, 0.204f, 1.000f},
	{0.133f, 0.545f, 0.133f, 1.000f},
	{0.926f, 0.741f, 0.173f, 1.000f},
	{0.482f, 0.408f, 0.933f, 1.000f},
	{0.698f, 1.000f, 1.000f, 1.000f},
	{0.525f, 0.314f, 0.251f, 1.000f},
	{0.859f, 0.843f, 0.824f, 1.000f},
	{0.059f, 0.059f, 0.059f, 1.000f},
	{0.396f, 0.000f, 0.043f, 1.000f},
	{0.482f, 0.471f, 0.353f, 1.000f},
	{0.875f, 0.616f, 0.357f, 1.000f},
	{0.208f, 0.369f, 0.310f, 1.000f},
	{0.208f, 0.318f, 0.310f, 1.000f},
	{0.557f, 0.349f, 0.235f, 1.000f},
	{0.980f, 0.941f, 0.745f, 1.000f},
	{0.063f, 0.047f, 0.031f, 1.000f},
	{1.000f, 0.012f, 0.243f, 1.000f},
	{0.224f, 1.000f, 0.078f, 1.000f},
	{0.980f, 0.929f, 0.153f, 1.000f},
	{0.071f, 0.039f, 0.561f, 1.000f},
	{0.000f, 1.000f, 0.937f, 1.000f},
	{0.545f, 0.000f, 0.545f, 1.000f},
	{0.667f, 0.941f, 0.820f, 1.000f},
	{0.827f, 0.827f, 0.827f, 1.000f},
	{1.000f, 0.600f, 0.600f, 1.000f},
	{0.565f, 0.933f, 0.565f, 1.000f},
	};


vec3_t	bytedirs[NUMVERTEXNORMALS] =
{
{-0.525731f, 0.000000f, 0.850651f}, {-0.442863f, 0.238856f, 0.864188f}, 
{-0.295242f, 0.000000f, 0.955423f}, {-0.309017f, 0.500000f, 0.809017f}, 
{-0.162460f, 0.262866f, 0.951056f}, {0.000000f, 0.000000f, 1.000000f}, 
{0.000000f, 0.850651f, 0.525731f}, {-0.147621f, 0.716567f, 0.681718f}, 
{0.147621f, 0.716567f, 0.681718f}, {0.000000f, 0.525731f, 0.850651f}, 
{0.309017f, 0.500000f, 0.809017f}, {0.525731f, 0.000000f, 0.850651f}, 
{0.295242f, 0.000000f, 0.955423f}, {0.442863f, 0.238856f, 0.864188f}, 
{0.162460f, 0.262866f, 0.951056f}, {-0.681718f, 0.147621f, 0.716567f}, 
{-0.809017f, 0.309017f, 0.500000f},{-0.587785f, 0.425325f, 0.688191f}, 
{-0.850651f, 0.525731f, 0.000000f},{-0.864188f, 0.442863f, 0.238856f}, 
{-0.716567f, 0.681718f, 0.147621f},{-0.688191f, 0.587785f, 0.425325f}, 
{-0.500000f, 0.809017f, 0.309017f}, {-0.238856f, 0.864188f, 0.442863f}, 
{-0.425325f, 0.688191f, 0.587785f}, {-0.716567f, 0.681718f, -0.147621f}, 
{-0.500000f, 0.809017f, -0.309017f}, {-0.525731f, 0.850651f, 0.000000f}, 
{0.000000f, 0.850651f, -0.525731f}, {-0.238856f, 0.864188f, -0.442863f}, 
{0.000000f, 0.955423f, -0.295242f}, {-0.262866f, 0.951056f, -0.162460f}, 
{0.000000f, 1.000000f, 0.000000f}, {0.000000f, 0.955423f, 0.295242f}, 
{-0.262866f, 0.951056f, 0.162460f}, {0.238856f, 0.864188f, 0.442863f}, 
{0.262866f, 0.951056f, 0.162460f}, {0.500000f, 0.809017f, 0.309017f}, 
{0.238856f, 0.864188f, -0.442863f},{0.262866f, 0.951056f, -0.162460f}, 
{0.500000f, 0.809017f, -0.309017f},{0.850651f, 0.525731f, 0.000000f}, 
{0.716567f, 0.681718f, 0.147621f}, {0.716567f, 0.681718f, -0.147621f}, 
{0.525731f, 0.850651f, 0.000000f}, {0.425325f, 0.688191f, 0.587785f}, 
{0.864188f, 0.442863f, 0.238856f}, {0.688191f, 0.587785f, 0.425325f}, 
{0.809017f, 0.309017f, 0.500000f}, {0.681718f, 0.147621f, 0.716567f}, 
{0.587785f, 0.425325f, 0.688191f}, {0.955423f, 0.295242f, 0.000000f}, 
{1.000000f, 0.000000f, 0.000000f}, {0.951056f, 0.162460f, 0.262866f}, 
{0.850651f, -0.525731f, 0.000000f},{0.955423f, -0.295242f, 0.000000f}, 
{0.864188f, -0.442863f, 0.238856f}, {0.951056f, -0.162460f, 0.262866f}, 
{0.809017f, -0.309017f, 0.500000f}, {0.681718f, -0.147621f, 0.716567f}, 
{0.850651f, 0.000000f, 0.525731f}, {0.864188f, 0.442863f, -0.238856f}, 
{0.809017f, 0.309017f, -0.500000f}, {0.951056f, 0.162460f, -0.262866f}, 
{0.525731f, 0.000000f, -0.850651f}, {0.681718f, 0.147621f, -0.716567f}, 
{0.681718f, -0.147621f, -0.716567f},{0.850651f, 0.000000f, -0.525731f}, 
{0.809017f, -0.309017f, -0.500000f}, {0.864188f, -0.442863f, -0.238856f}, 
{0.951056f, -0.162460f, -0.262866f}, {0.147621f, 0.716567f, -0.681718f}, 
{0.309017f, 0.500000f, -0.809017f}, {0.425325f, 0.688191f, -0.587785f}, 
{0.442863f, 0.238856f, -0.864188f}, {0.587785f, 0.425325f, -0.688191f}, 
{0.688191f, 0.587785f, -0.425325f}, {-0.147621f, 0.716567f, -0.681718f}, 
{-0.309017f, 0.500000f, -0.809017f}, {0.000000f, 0.525731f, -0.850651f}, 
{-0.525731f, 0.000000f, -0.850651f}, {-0.442863f, 0.238856f, -0.864188f}, 
{-0.295242f, 0.000000f, -0.955423f}, {-0.162460f, 0.262866f, -0.951056f}, 
{0.000000f, 0.000000f, -1.000000f}, {0.295242f, 0.000000f, -0.955423f}, 
{0.162460f, 0.262866f, -0.951056f}, {-0.442863f, -0.238856f, -0.864188f}, 
{-0.309017f, -0.500000f, -0.809017f}, {-0.162460f, -0.262866f, -0.951056f}, 
{0.000000f, -0.850651f, -0.525731f}, {-0.147621f, -0.716567f, -0.681718f}, 
{0.147621f, -0.716567f, -0.681718f}, {0.000000f, -0.525731f, -0.850651f}, 
{0.309017f, -0.500000f, -0.809017f}, {0.442863f, -0.238856f, -0.864188f}, 
{0.162460f, -0.262866f, -0.951056f}, {0.238856f, -0.864188f, -0.442863f}, 
{0.500000f, -0.809017f, -0.309017f}, {0.425325f, -0.688191f, -0.587785f}, 
{0.716567f, -0.681718f, -0.147621f}, {0.688191f, -0.587785f, -0.425325f}, 
{0.587785f, -0.425325f, -0.688191f}, {0.000000f, -0.955423f, -0.295242f}, 
{0.000000f, -1.000000f, 0.000000f}, {0.262866f, -0.951056f, -0.162460f}, 
{0.000000f, -0.850651f, 0.525731f}, {0.000000f, -0.955423f, 0.295242f}, 
{0.238856f, -0.864188f, 0.442863f}, {0.262866f, -0.951056f, 0.162460f}, 
{0.500000f, -0.809017f, 0.309017f}, {0.716567f, -0.681718f, 0.147621f}, 
{0.525731f, -0.850651f, 0.000000f}, {-0.238856f, -0.864188f, -0.442863f}, 
{-0.500000f, -0.809017f, -0.309017f}, {-0.262866f, -0.951056f, -0.162460f}, 
{-0.850651f, -0.525731f, 0.000000f}, {-0.716567f, -0.681718f, -0.147621f}, 
{-0.716567f, -0.681718f, 0.147621f}, {-0.525731f, -0.850651f, 0.000000f}, 
{-0.500000f, -0.809017f, 0.309017f}, {-0.238856f, -0.864188f, 0.442863f}, 
{-0.262866f, -0.951056f, 0.162460f}, {-0.864188f, -0.442863f, 0.238856f}, 
{-0.809017f, -0.309017f, 0.500000f}, {-0.688191f, -0.587785f, 0.425325f}, 
{-0.681718f, -0.147621f, 0.716567f}, {-0.442863f, -0.238856f, 0.864188f}, 
{-0.587785f, -0.425325f, 0.688191f}, {-0.309017f, -0.500000f, 0.809017f}, 
{-0.147621f, -0.716567f, 0.681718f}, {-0.425325f, -0.688191f, 0.587785f}, 
{-0.162460f, -0.262866f, 0.951056f}, {0.442863f, -0.238856f, 0.864188f}, 
{0.162460f, -0.262866f, 0.951056f}, {0.309017f, -0.500000f, 0.809017f}, 
{0.147621f, -0.716567f, 0.681718f}, {0.000000f, -0.525731f, 0.850651f}, 
{0.425325f, -0.688191f, 0.587785f}, {0.587785f, -0.425325f, 0.688191f}, 
{0.688191f, -0.587785f, 0.425325f}, {-0.955423f, 0.295242f, 0.000000f}, 
{-0.951056f, 0.162460f, 0.262866f}, {-1.000000f, 0.000000f, 0.000000f}, 
{-0.850651f, 0.000000f, 0.525731f}, {-0.955423f, -0.295242f, 0.000000f}, 
{-0.951056f, -0.162460f, 0.262866f}, {-0.864188f, 0.442863f, -0.238856f}, 
{-0.951056f, 0.162460f, -0.262866f}, {-0.809017f, 0.309017f, -0.500000f}, 
{-0.864188f, -0.442863f, -0.238856f}, {-0.951056f, -0.162460f, -0.262866f}, 
{-0.809017f, -0.309017f, -0.500000f}, {-0.681718f, 0.147621f, -0.716567f}, 
{-0.681718f, -0.147621f, -0.716567f}, {-0.850651f, 0.000000f, -0.525731f}, 
{-0.688191f, 0.587785f, -0.425325f}, {-0.587785f, 0.425325f, -0.688191f}, 
{-0.425325f, 0.688191f, -0.587785f}, {-0.425325f, -0.688191f, -0.587785f}, 
{-0.587785f, -0.425325f, -0.688191f}, {-0.688191f, -0.587785f, -0.425325f}
};

//==============================================================

void	Q_GetVectFromHexColor(const char *color_code, vec4_t color) {
	const char *c = color_code + 1; // skip Q_COLOR_ESCAPE
	int  i;
	qboolean is_short_hex_color;

	assert(color);
	assert(color_code);
	assert(Q_IsColorString(color_code));
	assert(Q_IsHexColor(c));

	//clear to color
	for(i = 0; i < 4; i++) {
		color[i] = 0;
	}

	is_short_hex_color = Q_IsShortHexColor(c);

	//skip Q_COLOR_HEX_ESCAPE
	c++;

	//the long hex color format uses and extra Q_COLOR_HEX_ESCAPE
	if(!is_short_hex_color) {
		c++;
	}

	//convert the particular hex character
	for(i = 0; i < Q_NumOfColorCodeDigits(color_code); i++) {
		int val;

		if(isdigit(*c)) {
			val = *c - '0';
		} else {
			switch (tolower(*c)) {
				case 'a':
					val = 10;
					break;
				case 'b':
					val = 11;
					break;
				case 'c':
					val = 12;
					break;
				case 'd':
					val = 13;
					break;
				case 'e':
					val = 14;
					break;
				case 'f':
					val = 15;
					break;

				default:
					val = 15;
			}
		}

		if(!is_short_hex_color) {
			// determine if this is the first or seconad charcter of the particul hex value
			if((i % 2) == 0) {
				val *= 16;
			}
		}

		//set the appropriate absulute color values
		if(i < (is_short_hex_color ? 1 : 2)) {
			color[0] += val;
		} else if(i < (is_short_hex_color ? 2 : 4)) {
			color[1] += val;
		} else if(i < (is_short_hex_color ? 3 : 6)) {
			color[2] += val;
		}

		//increment to the next hex color character.
		c++;
	}

	//convert color values to a fractional value
	if(is_short_hex_color) {
		for(i = 0; i < 3; i++) {
			color[i] = color[i] / 15;
		}
	} else {
		for(i = 0; i < 3; i++) {
			color[i] = color[i] / 255;
		}
	}

	//always opaque
	color[3] = 1;
}

int Q_ApproxBasicColorIndexFromVectColor(const vec4_t color) {
	int			best_index = 7;
	int			i;
	float		best_color_distance = 2.0;

	for(i = 0; i < 8; i++) {
		vec4_t   basic_color;
		vec3_t   color_diff;
		float    distance;
		int      j;

		Vector4Copy(g_color_table[i], basic_color);
		for(j = 0; j < 3; j++) {
			color_diff[j] = color[j] - basic_color[j];
		}

		distance = VectorLength(color_diff);

		if(distance < best_color_distance) {
			best_color_distance = distance;
			best_index = i;
		}
	}

	return best_index;
}

//==============================================================

int		Q_rand( int *seed ) {
	*seed = (69069 * *seed + 1);
	return *seed;
}

float	Q_random( int *seed ) {
	return ( Q_rand( seed ) & 0xffff ) / (float)0x10000;
}

float	Q_crandom( int *seed ) {
	return 2.0 * ( Q_random( seed ) - 0.5 );
}

//=======================================================

signed char ClampChar( int i ) {
	if ( i < -128 ) {
		return -128;
	}
	if ( i > 127 ) {
		return 127;
	}
	return i;
}

signed short ClampShort( int i ) {
	if ( i < -32768 ) {
		return -32768;
	}
	if ( i > 0x7fff ) {
		return 0x7fff;
	}
	return i;
}


// this isn't a real cheap function to call!
int DirToByte( vec3_t dir ) {
	int		i, best;
	float	d, bestd;

	if ( !dir ) {
		return 0;
	}

	bestd = 0;
	best = 0;
	for (i=0 ; i<NUMVERTEXNORMALS ; i++)
	{
		d = DotProduct (dir, bytedirs[i]);
		if (d > bestd)
		{
			bestd = d;
			best = i;
		}
	}

	return best;
}

void ByteToDir( int b, vec3_t dir ) {
	if ( b < 0 || b >= NUMVERTEXNORMALS ) {
		VectorCopy( vec3_origin, dir );
		return;
	}
	VectorCopy (bytedirs[b], dir);
}


unsigned ColorBytes3 (float r, float g, float b) {
	unsigned	i;

	( (byte *)&i )[0] = r * 255;
	( (byte *)&i )[1] = g * 255;
	( (byte *)&i )[2] = b * 255;

	return i;
}

unsigned ColorBytes4 (float r, float g, float b, float a) {
	unsigned	i;

	( (byte *)&i )[0] = r * 255;
	( (byte *)&i )[1] = g * 255;
	( (byte *)&i )[2] = b * 255;
	( (byte *)&i )[3] = a * 255;

	return i;
}

float NormalizeColor( const vec3_t in, vec3_t out ) {
	float	max;
	
	max = in[0];
	if ( in[1] > max ) {
		max = in[1];
	}
	if ( in[2] > max ) {
		max = in[2];
	}

	if ( !max ) {
		VectorClear( out );
	} else {
		out[0] = in[0] / max;
		out[1] = in[1] / max;
		out[2] = in[2] / max;
	}
	return max;
}


/*
=====================
PlaneFromPoints

Returns false if the triangle is degenrate.
The normal will point out of the clock for clockwise ordered points
=====================
*/
qboolean PlaneFromPoints( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c ) {
	vec3_t	d1, d2;

	VectorSubtract( b, a, d1 );
	VectorSubtract( c, a, d2 );
	CrossProduct( d2, d1, plane );
	if ( VectorNormalize( plane ) == 0 ) {
		return qfalse;
	}

	plane[3] = DotProduct( a, plane );
	return qtrue;
}

/*
===============
RotatePointAroundVector

This is not implemented very well...
===============
*/
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point,
							 float degrees ) {
	float sin_a;
	float cos_a;
	float cos_ia;
	float i_i_ia;
	float j_j_ia;
	float k_k_ia;
	float i_j_ia;
	float i_k_ia;
	float j_k_ia;
	float a_sin;
	float b_sin;
	float c_sin;
	float rot[3][3];

	cos_ia = DEG2RAD(degrees);
	sin_a = sin(cos_ia);
	cos_a = cos(cos_ia);
	cos_ia = 1.0F - cos_a;

	i_i_ia = dir[0] * dir[0] * cos_ia;
	j_j_ia = dir[1] * dir[1] * cos_ia;
	k_k_ia = dir[2] * dir[2] * cos_ia;
	i_j_ia = dir[0] * dir[1] * cos_ia;
	i_k_ia = dir[0] * dir[2] * cos_ia;
	j_k_ia = dir[1] * dir[2] * cos_ia;

	a_sin = dir[0] * sin_a;
	b_sin = dir[1] * sin_a;
	c_sin = dir[2] * sin_a;

	rot[0][0] = i_i_ia + cos_a;
	rot[0][1] = i_j_ia - c_sin;
	rot[0][2] = i_k_ia + b_sin;
	rot[1][0] = i_j_ia + c_sin;
	rot[1][1] = j_j_ia + cos_a;
	rot[1][2] = j_k_ia - a_sin;
	rot[2][0] = i_k_ia - b_sin;
	rot[2][1] = j_k_ia + a_sin;
	rot[2][2] = k_k_ia + cos_a;

	dst[0] = point[0] * rot[0][0] + point[1] * rot[0][1] + point[2] * rot[0][2];
	dst[1] = point[0] * rot[1][0] + point[1] * rot[1][1] + point[2] * rot[1][2];
	dst[2] = point[0] * rot[2][0] + point[1] * rot[2][1] + point[2] * rot[2][2];
}

/*
===============
RotateAroundDirection
===============
*/
void RotateAroundDirection( vec3_t axis[3], vec_t angle ) {
	vec_t scale;

	angle = DEG2RAD( angle );

	// create an arbitrary axis[1]
	PerpendicularVector( axis[ 1 ], axis[ 0 ] );

	// cross to get axis[2]
	CrossProduct( axis[ 0 ], axis[ 1 ], axis[ 2 ] );

	// rotate
	scale = cos( angle );
	VectorScale( axis[ 1 ], scale, axis[ 1 ] );

	scale = sin( angle );
	VectorMA( axis[ 1 ], scale, axis[ 2 ], axis[ 1 ] );

	// recalculate axis[2]
	CrossProduct( axis[ 0 ], axis[ 1 ], axis[ 2 ] );
}



void vectoangles( const vec3_t value1, vec3_t angles ) {
	float	forward;
	float	yaw, pitch;
	
	if ( value1[1] == 0 && value1[0] == 0 ) {
		yaw = 0;
		if ( value1[2] > 0 ) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if ( value1[0] ) {
			yaw = ( atan2 ( value1[1], value1[0] ) * 180 / M_PI );
		}
		else if ( value1[1] > 0 ) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if ( yaw < 0 ) {
			yaw += 360;
		}

		forward = sqrt ( value1[0]*value1[0] + value1[1]*value1[1] );
		pitch = ( atan2(value1[2], forward) * 180 / M_PI );
		if ( pitch < 0 ) {
			pitch += 360;
		}
	}

	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = 0;
}


/*
=================
AxisToAngles

Takes an axis (forward + right + up)
and returns angles -- including a roll
=================
*/
void AxisToAngles( vec3_t axis[3], vec3_t angles ) {
	float length1;
	float yaw, pitch, roll = 0.0f;

	if ( axis[0][1] == 0 && axis[0][0] == 0 ) {
		yaw = 0;
		if ( axis[0][2] > 0 ) {
			pitch = 90;
		}
		else {
			pitch = 270;
		}
	}
	else {
		if ( axis[0][0] ) {
			yaw = ( atan2 ( axis[0][1], axis[0][0] ) * 180 / M_PI );
		}
		else if ( axis[0][1] > 0 ) {
			yaw = 90;
		}
		else {
			yaw = 270;
		}
		if ( yaw < 0 ) {
			yaw += 360;
		}

		length1 = sqrt ( axis[0][0]*axis[0][0] + axis[0][1]*axis[0][1] );
		pitch = ( atan2(axis[0][2], length1) * 180 / M_PI );
		if ( pitch < 0 ) {
			pitch += 360;
		}

		roll = ( atan2( axis[1][2], axis[2][2] ) * 180 / M_PI );
		if ( roll < 0 ) {
			roll += 360;
		}
	}

	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = roll;
}

/*
=================
AnglesToAxis
=================
*/
void AnglesToAxis( const vec3_t angles, vec3_t axis[3] ) {
	vec3_t	right;

	// angle vectors returns "right" instead of "y axis"
	AngleVectors( angles, axis[0], right, axis[2] );
	VectorSubtract( vec3_origin, right, axis[1] );
}

void AxisClear( vec3_t axis[3] ) {
	axis[0][0] = 1;
	axis[0][1] = 0;
	axis[0][2] = 0;
	axis[1][0] = 0;
	axis[1][1] = 1;
	axis[1][2] = 0;
	axis[2][0] = 0;
	axis[2][1] = 0;
	axis[2][2] = 1;
}

void AxisCopy( vec3_t in[3], vec3_t out[3] ) {
	VectorCopy( in[0], out[0] );
	VectorCopy( in[1], out[1] );
	VectorCopy( in[2], out[2] );
}

void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal )
{
	float d;
	vec3_t n;
	float inv_denom;

	inv_denom = 1.0f / DotProduct( normal, normal );
#ifndef Q3_VM
	assert( Q_fabs(inv_denom) != 0.0f ); // zero vectors get here
#endif
	inv_denom = 1.0f / inv_denom;

	d = DotProduct( normal, p ) * inv_denom;

	n[0] = normal[0] * inv_denom;
	n[1] = normal[1] * inv_denom;
	n[2] = normal[2] * inv_denom;

	dst[0] = p[0] - d * n[0];
	dst[1] = p[1] - d * n[1];
	dst[2] = p[2] - d * n[2];
}

/*
================
MakeNormalVectors

Given a normalized forward vector, create two
other perpendicular vectors
================
*/
void MakeNormalVectors( const vec3_t forward, vec3_t right, vec3_t up) {
	float		d;

	// this rotate and negate guarantees a vector
	// not colinear with the original
	right[1] = -forward[0];
	right[2] = forward[1];
	right[0] = forward[2];

	d = DotProduct (right, forward);
	VectorMA (right, -d, forward, right);
	VectorNormalize (right);
	CrossProduct (right, forward, up);
}


void VectorRotate( vec3_t in, vec3_t matrix[3], vec3_t out )
{
	out[0] = DotProduct( in, matrix[0] );
	out[1] = DotProduct( in, matrix[1] );
	out[2] = DotProduct( in, matrix[2] );
}

//============================================================================

#if !idppc
/*
** float q_rsqrt( float number )
*/
float Q_rsqrt( float number )
{
	floatint_t t;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	t.f  = number;
	t.i  = 0x5f3759df - ( t.i >> 1 );               // what the fuck?
	y  = t.f;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

float Q_fabs( float f ) {
	floatint_t fi;
	fi.f = f;
	fi.i &= 0x7FFFFFFF;
	return fi.f;
}
#endif

//============================================================

/*
===============
LerpAngle

===============
*/
float LerpAngle (float from, float to, float frac) {
	float	a;

	if ( to - from > 180 ) {
		to -= 360;
	}
	if ( to - from < -180 ) {
		to += 360;
	}
	a = from + frac * (to - from);

	return a;
}


/*
=================
AngleSubtract

Always returns a value from -180 to 180
=================
*/
float	AngleSubtract( float a1, float a2 ) {
	float	a;

	a = a1 - a2;
	while ( a > 180 ) {
		a -= 360;
	}
	while ( a < -180 ) {
		a += 360;
	}
	return a;
}


void AnglesSubtract( vec3_t v1, vec3_t v2, vec3_t v3 ) {
	v3[0] = AngleSubtract( v1[0], v2[0] );
	v3[1] = AngleSubtract( v1[1], v2[1] );
	v3[2] = AngleSubtract( v1[2], v2[2] );
}


float	AngleMod(float a) {
	a = (360.0/65536) * ((int)(a*(65536/360.0)) & 65535);
	return a;
}


/*
=================
AngleNormalize360

returns angle normalized to the range [0 <= angle < 360]
=================
*/
float AngleNormalize360 ( float angle ) {
	return (360.0 / 65536) * ((int)(angle * (65536 / 360.0)) & 65535);
}


/*
=================
AngleNormalize180

returns angle normalized to the range [-180 < angle <= 180]
=================
*/
float AngleNormalize180 ( float angle ) {
	angle = AngleNormalize360( angle );
	if ( angle > 180.0 ) {
		angle -= 360.0;
	}
	return angle;
}


/*
=================
AngleDelta

returns the normalized delta from angle1 to angle2
=================
*/
float AngleDelta ( float angle1, float angle2 ) {
	return AngleNormalize180( angle1 - angle2 );
}


//============================================================


/*
=================
SetPlaneSignbits
=================
*/
void SetPlaneSignbits (cplane_t *out) {
	int	bits, j;

	// for fast box on planeside test
	bits = 0;
	for (j=0 ; j<3 ; j++) {
		if (out->normal[j] < 0) {
			bits |= 1<<j;
		}
	}
	out->signbits = bits;
}


/*
==================
BoxOnPlaneSide

Returns 1, 2, or 1 + 2
==================
*/
int BoxOnPlaneSide(vec3_t emins, vec3_t emaxs, struct cplane_s *p)
{
	float	dist[2];
	int		sides, b, i;

	// fast axial cases
	if (p->type < 3)
	{
		if (p->dist <= emins[p->type])
			return 1;
		if (p->dist >= emaxs[p->type])
			return 2;
		return 3;
	}

	// general case
	dist[0] = dist[1] = 0;
	if (p->signbits < 8) // >= 8: default case is original code (dist[0]=dist[1]=0)
	{
		for (i=0 ; i<3 ; i++)
		{
			b = (p->signbits >> i) & 1;
			dist[ b] += p->normal[i]*emaxs[i];
			dist[!b] += p->normal[i]*emins[i];
		}
	}

	sides = 0;
	if (dist[0] >= p->dist)
		sides = 1;
	if (dist[1] < p->dist)
		sides |= 2;

	return sides;
}


/*
=================
RadiusFromBounds
=================
*/
float RadiusFromBounds( const vec3_t mins, const vec3_t maxs ) {
	int		i;
	vec3_t	corner;
	float	a, b;

	for (i=0 ; i<3 ; i++) {
		a = fabs( mins[i] );
		b = fabs( maxs[i] );
		corner[i] = a > b ? a : b;
	}

	return VectorLength (corner);
}


void ClearBounds( vec3_t mins, vec3_t maxs ) {
	mins[0] = mins[1] = mins[2] = 99999;
	maxs[0] = maxs[1] = maxs[2] = -99999;
}

void AddPointToBounds( const vec3_t v, vec3_t mins, vec3_t maxs ) {
	if ( v[0] < mins[0] ) {
		mins[0] = v[0];
	}
	if ( v[0] > maxs[0]) {
		maxs[0] = v[0];
	}

	if ( v[1] < mins[1] ) {
		mins[1] = v[1];
	}
	if ( v[1] > maxs[1]) {
		maxs[1] = v[1];
	}

	if ( v[2] < mins[2] ) {
		mins[2] = v[2];
	}
	if ( v[2] > maxs[2]) {
		maxs[2] = v[2];
	}
}

qboolean BoundsIntersect(const vec3_t mins, const vec3_t maxs,
		const vec3_t mins2, const vec3_t maxs2)
{
	if ( maxs[0] < mins2[0] ||
		maxs[1] < mins2[1] ||
		maxs[2] < mins2[2] ||
		mins[0] > maxs2[0] ||
		mins[1] > maxs2[1] ||
		mins[2] > maxs2[2])
	{
		return qfalse;
	}

	return qtrue;
}

qboolean BoundsIntersectSphere(const vec3_t mins, const vec3_t maxs,
		const vec3_t origin, vec_t radius)
{
	if ( origin[0] - radius > maxs[0] ||
		origin[0] + radius < mins[0] ||
		origin[1] - radius > maxs[1] ||
		origin[1] + radius < mins[1] ||
		origin[2] - radius > maxs[2] ||
		origin[2] + radius < mins[2])
	{
		return qfalse;
	}

	return qtrue;
}

qboolean BoundsIntersectPoint(const vec3_t mins, const vec3_t maxs,
		const vec3_t origin)
{
	if ( origin[0] > maxs[0] ||
		origin[0] < mins[0] ||
		origin[1] > maxs[1] ||
		origin[1] < mins[1] ||
		origin[2] > maxs[2] ||
		origin[2] < mins[2])
	{
		return qfalse;
	}

	return qtrue;
}

vec_t VectorNormalize( vec3_t v ) {
	float	length, ilength;

	length = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];

	if ( length ) {
		/* writing it this way allows gcc to recognize that rsqrt can be used */
		ilength = 1/(float)sqrt (length);
		/* sqrt(length) = length * (1 / sqrt(length)) */
		length *= ilength;
		v[0] *= ilength;
		v[1] *= ilength;
		v[2] *= ilength;
	}
		
	return length;
}

vec_t VectorNormalize2( const vec3_t v, vec3_t out) {
	float	length, ilength;

	length = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];

	if (length)
	{
		/* writing it this way allows gcc to recognize that rsqrt can be used */
		ilength = 1/(float)sqrt (length);
		/* sqrt(length) = length * (1 / sqrt(length)) */
		length *= ilength;
		out[0] = v[0]*ilength;
		out[1] = v[1]*ilength;
		out[2] = v[2]*ilength;
	} else {
		VectorClear( out );
	}
		
	return length;

}

void _VectorMA( const vec3_t veca, float scale, const vec3_t vecb, vec3_t vecc) {
	vecc[0] = veca[0] + scale*vecb[0];
	vecc[1] = veca[1] + scale*vecb[1];
	vecc[2] = veca[2] + scale*vecb[2];
}


vec_t _DotProduct( const vec3_t v1, const vec3_t v2 ) {
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

void _VectorSubtract( const vec3_t veca, const vec3_t vecb, vec3_t out ) {
	out[0] = veca[0]-vecb[0];
	out[1] = veca[1]-vecb[1];
	out[2] = veca[2]-vecb[2];
}

void _VectorAdd( const vec3_t veca, const vec3_t vecb, vec3_t out ) {
	out[0] = veca[0]+vecb[0];
	out[1] = veca[1]+vecb[1];
	out[2] = veca[2]+vecb[2];
}

void _VectorCopy( const vec3_t in, vec3_t out ) {
	out[0] = in[0];
	out[1] = in[1];
	out[2] = in[2];
}

void _VectorScale( const vec3_t in, vec_t scale, vec3_t out ) {
	out[0] = in[0]*scale;
	out[1] = in[1]*scale;
	out[2] = in[2]*scale;
}

void Vector4Scale( const vec4_t in, vec_t scale, vec4_t out ) {
	out[0] = in[0]*scale;
	out[1] = in[1]*scale;
	out[2] = in[2]*scale;
	out[3] = in[3]*scale;
}


int Q_log2( int val ) {
	int answer;

	answer = 0;
	while ( ( val>>=1 ) != 0 ) {
		answer++;
	}
	return answer;
}



/*
=================
PlaneTypeForNormal
=================
*/
/*
int	PlaneTypeForNormal (vec3_t normal) {
	if ( normal[0] == 1.0 )
		return PLANE_X;
	if ( normal[1] == 1.0 )
		return PLANE_Y;
	if ( normal[2] == 1.0 )
		return PLANE_Z;
	
	return PLANE_NON_AXIAL;
}
*/


/*
================
MatrixMultiply
================
*/
void MatrixMultiply(float in1[3][3], float in2[3][3], float out[3][3]) {
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
				in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
				in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
				in1[0][2] * in2[2][2];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
				in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
				in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
				in1[1][2] * in2[2][2];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
				in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
				in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
				in1[2][2] * in2[2][2];
}

/*
================
VectorMatrixMultiply
================
*/
void VectorMatrixMultiply( const vec3_t p, vec3_t m[ 3 ], vec3_t out )
{
	out[ 0 ] = m[ 0 ][ 0 ] * p[ 0 ] + m[ 1 ][ 0 ] * p[ 1 ] + m[ 2 ][ 0 ] * p[ 2 ];
	out[ 1 ] = m[ 0 ][ 1 ] * p[ 0 ] + m[ 1 ][ 1 ] * p[ 1 ] + m[ 2 ][ 1 ] * p[ 2 ];
	out[ 2 ] = m[ 0 ][ 2 ] * p[ 0 ] + m[ 1 ][ 2 ] * p[ 1 ] + m[ 2 ][ 2 ] * p[ 2 ];
}


void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up) {
	float		angle;
	static float		sr, sp, sy, cr, cp, cy;
	// static to help MS compiler fp bugs

	angle = angles[YAW] * (M_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[PITCH] * (M_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[ROLL] * (M_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	if (forward)
	{
		forward[0] = cp*cy;
		forward[1] = cp*sy;
		forward[2] = -sp;
	}
	if (right)
	{
		right[0] = (-1*sr*sp*cy+-1*cr*-sy);
		right[1] = (-1*sr*sp*sy+-1*cr*cy);
		right[2] = -1*sr*cp;
	}
	if (up)
	{
		up[0] = (cr*sp*cy+-sr*-sy);
		up[1] = (cr*sp*sy+-sr*cy);
		up[2] = cr*cp;
	}
}

/*
** assumes "src" is normalized
*/
void PerpendicularVector( vec3_t dst, const vec3_t src )
{
	int	pos;
	int i;
	float minelem = 1.0F;
	vec3_t tempvec;

	/*
	** find the smallest magnitude axially aligned vector
	*/
	for ( pos = 0, i = 0; i < 3; i++ )
	{
		if ( fabs( src[i] ) < minelem )
		{
			pos = i;
			minelem = fabs( src[i] );
		}
	}
	tempvec[0] = tempvec[1] = tempvec[2] = 0.0F;
	tempvec[pos] = 1.0F;

	/*
	** project the point onto the plane defined by src
	*/
	ProjectPointOnPlane( dst, tempvec, src );

	/*
	** normalize the result
	*/
	VectorNormalize( dst );
}

/*
=================
pointToLineDistance

Distance from a point to some line
=================
*/
float pointToLineDistance( const vec3_t p0, const vec3_t p1, const vec3_t p2 )
{
	vec3_t	v, w, y;
	float	 c1, c2;

	VectorSubtract( p2, p1, v );
	VectorSubtract( p1, p0, w );

	CrossProduct( w, v, y );
	c1 = VectorLength( y );
	c2 = VectorLength( v );

	if( c2 == 0.0f )
		return 0.0f;
	else
		return c1 / c2;
}

/*
=================
GetPerpendicularViewVector

Used to find an "up" vector for drawing a sprite so that it always faces the view as best as possible
=================
*/
void GetPerpendicularViewVector( const vec3_t point, const vec3_t p1, const vec3_t p2, vec3_t up )
{
	vec3_t	v1, v2;

	VectorSubtract( point, p1, v1 );
	VectorNormalize( v1 );

	VectorSubtract( point, p2, v2 );
	VectorNormalize( v2 );

	CrossProduct( v1, v2, up );
	VectorNormalize( up );
}

/*
================
ProjectPointOntoVector
================
*/
void ProjectPointOntoVector( vec3_t point, vec3_t vStart, vec3_t vEnd, vec3_t vProj )
{
	vec3_t pVec, vec;

	VectorSubtract( point, vStart, pVec );
	VectorSubtract( vEnd, vStart, vec );
	VectorNormalize( vec );
	// project onto the directional vector for this segment
	VectorMA( vStart, DotProduct( pVec, vec ), vec, vProj );
}

/*
================
VectorMaxComponent

Return the biggest component of some vector
================
*/
float VectorMaxComponent( vec3_t v )
{
	float biggest = v[ 0 ];

	if( v[ 1 ] > biggest )
		biggest = v[ 1 ];

	if( v[ 2 ] > biggest )
		biggest = v[ 2 ];

	return biggest;
}

/*
================
VectorMinComponent

Return the smallest component of some vector
================
*/
float VectorMinComponent( vec3_t v )
{
	float smallest = v[ 0 ];

	if( v[ 1 ] < smallest )
		smallest = v[ 1 ];

	if( v[ 2 ] < smallest )
		smallest = v[ 2 ];

	return smallest;
}


#define LINE_DISTANCE_EPSILON 1e-05f

/*
================
DistanceBetweenLineSegmentsSquared

Return the smallest distance between two line segments, squared
================
*/
vec_t DistanceBetweenLineSegmentsSquared(
    const vec3_t sP0, const vec3_t sP1,
    const vec3_t tP0, const vec3_t tP1,
    float *s, float *t )
{
  vec3_t  sMag, tMag, diff;
  float   a, b, c, d, e;
  float   D;
  float   sN, sD;
  float   tN, tD;
  vec3_t  separation;

  VectorSubtract( sP1, sP0, sMag );
  VectorSubtract( tP1, tP0, tMag );
  VectorSubtract( sP0, tP0, diff );
  a = DotProduct( sMag, sMag );
  b = DotProduct( sMag, tMag );
  c = DotProduct( tMag, tMag );
  d = DotProduct( sMag, diff );
  e = DotProduct( tMag, diff );
  sD = tD = D = a * c - b * b;

  if( D < LINE_DISTANCE_EPSILON )
  {
    // the lines are almost parallel
    sN = 0.0;   // force using point P0 on segment S1
    sD = 1.0;   // to prevent possible division by 0.0 later
    tN = e;
    tD = c;
  }
  else
  {
    // get the closest points on the infinite lines
    sN = ( b * e - c * d );
    tN = ( a * e - b * d );

    if( sN < 0.0 )
    {
      // sN < 0 => the s=0 edge is visible
      sN = 0.0;
      tN = e;
      tD = c;
    }
    else if( sN > sD )
    {
      // sN > sD => the s=1 edge is visible
      sN = sD;
      tN = e + b;
      tD = c;
    }
  }

  if( tN < 0.0 )
  {
    // tN < 0 => the t=0 edge is visible
    tN = 0.0;

    // recompute sN for this edge
    if( -d < 0.0 )
      sN = 0.0;
    else if( -d > a )
      sN = sD;
    else
    {
      sN = -d;
      sD = a;
    }
  }
  else if( tN > tD )
  {
    // tN > tD => the t=1 edge is visible
    tN = tD;

    // recompute sN for this edge
    if( ( -d + b ) < 0.0 )
      sN = 0;
    else if( ( -d + b ) > a )
      sN = sD;
    else
    {
      sN = ( -d + b );
      sD = a;
    }
  }

  // finally do the division to get *s and *t
  *s = ( fabs( sN ) < LINE_DISTANCE_EPSILON ? 0.0 : sN / sD );
  *t = ( fabs( tN ) < LINE_DISTANCE_EPSILON ? 0.0 : tN / tD );

  // get the difference of the two closest points
  VectorScale( sMag, *s, sMag );
  VectorScale( tMag, *t, tMag );
  VectorAdd( diff, sMag, separation );
  VectorSubtract( separation, tMag, separation );

  return VectorLengthSquared( separation );
}

/*
================
DistanceBetweenLineSegments

Return the smallest distance between two line segments
================
*/
vec_t DistanceBetweenLineSegments(
    const vec3_t sP0, const vec3_t sP1,
    const vec3_t tP0, const vec3_t tP1,
    float *s, float *t )
{
  return (vec_t)sqrt( DistanceBetweenLineSegmentsSquared(
        sP0, sP1, tP0, tP1, s, t ) );
}

/*
=================
Q_isnan

Don't pass doubles to this
================
*/
int Q_isnan( float x )
{
	floatint_t fi;

	fi.f = x;
	fi.ui &= 0x7FFFFFFF;
	fi.ui = 0x7F800000 - fi.ui;

	return (int)( (unsigned int)fi.ui >> 31 );
}

/*
==============================================================

Bucket Selection System

==============================================================
*/

typedef enum bucket_lists_s
{
	BUCKET_LIST_A = 0,
	BUCKET_LIST_B,

	NUM_BUCKET_LISTS
} bucket_lists_t;

typedef struct bucket_s
{
	void**         list[NUM_BUCKET_LISTS];
	unsigned int   list_length[NUM_BUCKET_LISTS];
	bucket_lists_t selection_list;
	unsigned int   bucket_size;
  qboolean           bucket_slot_used;
} bucket_t;

static bucket_t*    buckets = NULL;
static unsigned int num_buckets = 0;

static void Q_Bucket_Resize_Array_Of_Buckets(
	unsigned int new_num_buckets, void* (*qalloc)(int size),
	void (*qfree)(void *ptr)) {
	bucket_t*          old_buckets = buckets;
	unsigned int       num_buckets_to_copy;
	const unsigned int num_deleted_buckets =
		(num_buckets > new_num_buckets) ? (num_buckets - new_num_buckets) : 0;

	//free bucket lists for any buckets that will be deleted
	if(num_deleted_buckets > 0) {
		int i;

		for(i = num_buckets - num_deleted_buckets - 1; i < num_buckets ; i++) {
			int j;

			for(j = 0; j < NUM_BUCKET_LISTS; j++) {
				if(buckets[i].list[i]) {
					qfree(buckets[i].list[i]);
				}
			}
		}
	}

	if(new_num_buckets > 0) {
		buckets = (bucket_t *)qalloc(new_num_buckets * sizeof(bucket_t));

		if(new_num_buckets > num_buckets) {
			num_buckets_to_copy = num_buckets;
		} else {
			num_buckets_to_copy = new_num_buckets;
		}

		if(old_buckets) {
			memcpy(buckets, old_buckets, num_buckets_to_copy * sizeof(bucket_t));
		}
	} else {
		buckets = NULL;
	}

	num_buckets = new_num_buckets;

	if(old_buckets) {
		qfree(old_buckets);
	}
}

unsigned int Q_Bucket_Create_Bucket(
	void* (*qalloc)(int size), void (*qfree)(void *ptr)) {

	//check if there are currently any free slots for a new bucket
	if(num_buckets > 0) {
		int i;

		for(i = 0; i < num_buckets; i++) {
			if(!buckets[i].bucket_slot_used) {
				return i;
			}
		}
	}

	//create a new bucket slot, and return it
	Q_Bucket_Resize_Array_Of_Buckets((num_buckets + 1), qalloc, qfree);
	memset(&buckets[num_buckets - 1], 0, sizeof(bucket_t));
	buckets[num_buckets - 1].bucket_slot_used = qtrue;
	return num_buckets - 1;
}

void Q_Bucket_Delete_Bucket(unsigned int bucket_handle) {
	assert(
		(bucket_handle < num_buckets) &&
		buckets[bucket_handle].bucket_slot_used &&
		"Q_Bucket_Destroy_Bucket: bucket handle not found");

		buckets[bucket_handle].bucket_slot_used = qfalse;
}

void Q_Bucket_Destroy_All_Buckets(
	void* (*qalloc)(int size), void (*qfree)(void *ptr)) {
	Q_Bucket_Resize_Array_Of_Buckets(0, qalloc, qfree);
}

static void Q_Bucket_Resize_Bucket(
	unsigned int bucket_handle, unsigned int new_bucket_size,
	void* (*qalloc)(int size), void (*qfree)(void *ptr)) {
	void**       old_list[NUM_BUCKET_LISTS];
	unsigned int num_items_to_copy;
	int          i;

	assert(
		(bucket_handle < num_buckets) &&
		buckets[bucket_handle].bucket_slot_used &&
		"Q_Bucket_Resize_Bucket: bucket handle not found");

		for(i = 0; i < NUM_BUCKET_LISTS; i++) {
			old_list[i] = buckets[bucket_handle].list[i];
		}

		for(i = 0; i < NUM_BUCKET_LISTS; i++) {
			buckets[bucket_handle].list[i] =
			(void **)qalloc(new_bucket_size * sizeof(void*));
			memset(buckets[bucket_handle].list[i], 0, new_bucket_size * sizeof(void*));
		}

		if(new_bucket_size > buckets[bucket_handle].bucket_size) {
			num_items_to_copy = buckets[bucket_handle].bucket_size;
		} else {
			num_items_to_copy = new_bucket_size;
		}

		if(buckets[bucket_handle].bucket_size > 0) {
			for(i = 0; i < NUM_BUCKET_LISTS; i++) {
				if(old_list[i]) {
					memcpy(
						buckets[bucket_handle].list[i],
						old_list[i], num_items_to_copy * sizeof(void*));
					}
				}
		}

		buckets[bucket_handle].bucket_size = new_bucket_size;

	for(i = 0; i < NUM_BUCKET_LISTS; i++) {
		if(old_list[i]) {
			qfree(old_list[i]);
		}
	}
}

static void Q_Bucket_Add_Item_To_List(
	bucket_t *bucket, void* item, bucket_lists_t bucket_list) {
	int   list_length;

	assert(bucket && "Q_Bucket_Add_Item_To_List: bucket is NULL");

	list_length = bucket->list_length[bucket_list];

	assert(
		list_length < bucket->bucket_size &&
		"Q_Bucket_Add_Item_To_List: adding this item would exceed the bucket_size");

	//add the item to the end of the list
	bucket->list[bucket_list][list_length] = item;
	bucket->list_length[bucket_list]++;
}

static void Q_Bucket_Remove_Item_By_Index_From_List(
	bucket_t *bucket, unsigned int item_index, bucket_lists_t bucket_list) {
	int   list_length;

	assert(bucket && "Q_Bucket_Add_Item_To_List: bucket is NULL");

	list_length = bucket->list_length[bucket_list];

	assert(
		list_length > 0 &&
		"Q_Bucket_Add_Item_To_List: bucket list is empty");
	assert(
		item_index < list_length &&
		"Q_Bucket_Add_Item_To_List: item index exceeds bucket list length");

	//move the last item to the removed item slot
	bucket->list[bucket_list][item_index] =
	bucket->list[bucket_list][list_length - 1];
	//reduce the length of the list by 1
	bucket->list_length[bucket_list]--;
}

void Q_Bucket_Add_Item_To_Bucket(
	unsigned int bucket_handle, void* item,
	void* (*qalloc)(int size), void (*qfree)(void *ptr)) {

	assert(
		(bucket_handle < num_buckets) &&
		buckets[bucket_handle].bucket_slot_used &&
		"Q_Bucket_Add_Item_To_Bucket: bucket handle not found");

	Q_Bucket_Resize_Bucket(
		bucket_handle, buckets[bucket_handle].bucket_size + 1,
		qalloc, qfree);

	Q_Bucket_Add_Item_To_List(
		&buckets[bucket_handle], item,
		buckets[bucket_handle].selection_list);
}

void Q_Bucket_Remove_Item_From_Bucket(
	unsigned int bucket_handle, void* item,
	void* (*qalloc)(int size), void (*qfree)(void *ptr)) {
	bucket_t* bucket;
	qboolean item_found = qfalse;
	int  i;

	assert(
		(bucket_handle < num_buckets) &&
		buckets[bucket_handle].bucket_slot_used &&
		"Q_Bucket_Remove_Item_From_Bucket: bucket handle not found");
	assert(
		buckets[bucket_handle].bucket_size > 0 &&
		"Q_Bucket_Remove_Item_From_Bucket: bucket is empty");

	bucket = &buckets[bucket_handle];

	for(i = 0; i < NUM_BUCKET_LISTS; i++) {
		int j;

		for(j = 0; j < bucket->list_length[i]; j++) {
			if(bucket->list[i][j] == item) {
				bucket->list[i][j] =
					bucket->list[i][bucket->list_length[i] - 1];
				bucket->list_length[i]--;
				Q_Bucket_Resize_Bucket(
					bucket_handle, (buckets[bucket_handle].bucket_size - 1),
					qalloc, qfree);
				item_found = qtrue;
			}
		}
	}

	assert(
		item_found &&
		"Q_Bucket_Remove_Item_From_Bucket: item not found");
}

void* Q_Bucket_Select_A_Random_Item(unsigned int bucket_handle) {
	bucket_t     *bucket;
	unsigned int selected_item_index;
	void         *selected_item;

	assert(
		(bucket_handle < num_buckets) &&
		buckets[bucket_handle].bucket_slot_used &&
		"Q_Bucket_Select_A_Random_Item: bucket handle not found");
	assert(
		buckets[bucket_handle].bucket_size > 0 &&
		"Q_Bucket_Select_A_Random_Item: bucket is empty");

	bucket = &buckets[bucket_handle];

	//check if the selection list is empty
	if(bucket->list_length[bucket->selection_list] == 0) {
		if(bucket->selection_list == BUCKET_LIST_A) {
			bucket->selection_list = BUCKET_LIST_B;
		} else {
			bucket->selection_list = BUCKET_LIST_A;
		}
	}

	//select an item from the selection list
	selected_item_index = rand() % bucket->list_length[bucket->selection_list];
	selected_item = bucket->list[bucket->selection_list][selected_item_index];

	//move the item to the other list
	Q_Bucket_Remove_Item_By_Index_From_List(
		bucket, selected_item_index, bucket->selection_list);
	if(bucket->selection_list == BUCKET_LIST_A) {
		Q_Bucket_Add_Item_To_List(
			bucket, selected_item, BUCKET_LIST_B);
	} else {
		Q_Bucket_Add_Item_To_List(
			bucket, selected_item, BUCKET_LIST_A);
	}

	return selected_item;
}

void  Q_Bucket_Select_A_Specific_Item(unsigned int bucket_handle, void* item) {
	bucket_t     *bucket;
	unsigned int selected_item_index, i;
	void         *selected_item = NULL;

	assert(
		(bucket_handle < num_buckets) &&
		buckets[bucket_handle].bucket_slot_used &&
		"Q_Bucket_Select_A_Random_Item: bucket handle not found");
	assert(
		buckets[bucket_handle].bucket_size > 0 &&
		"Q_Bucket_Select_A_Random_Item: bucket is empty");

	bucket = &buckets[bucket_handle];

	//check if the selection list is empty
	if(bucket->list_length[bucket->selection_list] == 0) {
		if(bucket->selection_list == BUCKET_LIST_A) {
			bucket->selection_list = BUCKET_LIST_B;
		} else {
			bucket->selection_list = BUCKET_LIST_A;
		}
	}

	//search for the specific item
	for(i = 0; i < bucket->list_length[bucket->selection_list]; i++) {
		if(item == bucket->list[bucket->selection_list][i]) {
			selected_item_index = i;
			selected_item = item;
			break;
		}
	}

	assert(selected_item && "Q_Bucket_Select_A_Specific_Item: item not found");

	//move the item to the other list
	Q_Bucket_Remove_Item_By_Index_From_List(
		bucket, selected_item_index, bucket->selection_list);
	if(bucket->selection_list == BUCKET_LIST_A) {
		Q_Bucket_Add_Item_To_List(
			bucket, selected_item, BUCKET_LIST_B);
	} else {
		Q_Bucket_Add_Item_To_List(
			bucket, selected_item, BUCKET_LIST_A);
	}
}


//------------------------------------------------------------------------

#ifndef Q3_VM
/*
=====================
Q_acos

the msvc acos doesn't always return a value between -PI and PI:

int i;
i = 1065353246;
acos(*(float*) &i) == -1.#IND0

=====================
*/
float Q_acos(float c) {
	float angle;

	angle = acos(c);

	if (angle > M_PI) {
		return (float)M_PI;
	}
	if (angle < -M_PI) {
		return (float)M_PI;
	}
	return angle;
}
#endif
