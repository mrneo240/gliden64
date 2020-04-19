#include "Language.h"
#include "util.h"
#include <windows.h>
#include <algorithm>
#include <map>
#include "../Config.h"

typedef std::map<int32_t, std::string> LANG_STRINGS;
typedef LANG_STRINGS::value_type LANG_STR;

bool g_debugLang = false;
LANG_STRINGS g_currentStrings, g_defaultStrings;

void loadDefaultStrings(void)
{
    //Config Dialog
    g_defaultStrings.insert(LANG_STRINGS::value_type(TAB_VIDEO, "Video"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(TAB_EMULATION, "Emulation"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(TAB_FRAME_BUFFER, "Frame buffer"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(TAB_TEXTURE_ENHANCEMENT, "Texture enhancement"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(TAB_OSD, "OSD"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(TAB_DEBUG, "Debug"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_SAVE_SETTINGS_FOR, "Save settings for:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_SETTINGS_PROFILE, "Settings profile:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_REMOVE, "Remove"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_RESTORE_DEFAULTS, "Restore Defaults"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_SAVE_AND_CLOSE, "Save and Close"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_SAVE, "Save"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(CFG_CLOSE, "Close"));
    
    //Video Tab
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_GROUP, "Video"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_FULL_SCREEN_RES, "Full screen resolution:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_FULL_SCREEN_RES_TOOLTIP, "All the resolutions that your video card/monitor supports should be displayed.\n\n[Recommended: Maximum resolution for your monitor unless performance becomes an issue]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_REFRESH_RATE, "Refresh rate:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_REFRESH_RATE_TOOLTIP, ""));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_WINDOWED_RESOLUTION, "Windowed resolution:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_WINDOWED_RESOLUTION_TOOLTIP, "This option selects the resolution for windowed mode. You also may select Custom and enter your own window size.\n\n[Recommended: 640 x 480, 800 x 600, 1024 x 768, 1280 x 960]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ASPECT_RATIO, "Aspect ratio:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ASPECT_RATIO_TOOLTIP, "This setting adjusts the aspect ratio of the video output. All N64 games support 4:3. Some games support 16:9 within game settings. Use Stretch to fill the screen without pillar or letterboxing.\nTry to adjust game to fit tries to adjust the viewing space to fit without stretching. Many games work well adjusted, but some don't."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ASPECT_4_3, "4:3 (recommended)"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ASPECT_16_19, "16:9"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ASPECT_STRETCH, "Stretch"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ASPECT_ADJUST, "Try to adjust game to fit"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_VSYNC, "Enable VSync"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_VSYNC_TOOLTIP, "Vertical sync, or VSync, can improve the image by syncing the game's frame rate to your monitor's refresh rate.This prevents image tearing, but may cause performance problems.\n[Recommended:Usually off, on if you have image tearing problems]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_THREADED_VIDEO, "Enable threaded video"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_THREADED_VIDEO_TOOLTIP, "Threaded video can improve performance with poor OpenGL drivers at the cost of very marginal input lag, usually less than half a frame.\n[Recommended: Usually off, unless there are performance issues]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_OVERSCAN, "Overscan"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_OVERSCAN_TOOLTIP, "When enabled, the image is cropped by values specified in N64 pixels. Useful to remove black borders in some games."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_NTSC, "NTSC"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_PAL, "PAL"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ANTI_ALIASING, "Anti-aliasing"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_NO_ANTI_ALIASING, "No anti-aliasing"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_FAST_ANTI_ALIASING, "Fast approximate anti-aliasing (FXAA)"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_MULTISAMPLE_ANTI_ALIASING, "Multisample anti-aliasing (MSAA):"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_AA_OFF, "Off"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_AA_HIGH, "High"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_AA_TOOLTIP, "GLideN64 offers two methods to smooth jagged polygons:\nFast approximate anti-aliasing (FXAA): FXAA is a post-processing filter that can provide a decent result, but as good as MSAA. The main reason to use FXAA is to use with N64-style depth compare. FXAA adds some blurriness to the output image, causing some textures like text to possibly look worse.\nMultisample anti-aliasing (MSAA): MSAA is a standard anti-aliasing technique used in computer graphics to improve image quality. Most modern GPUs support 2, 4, 8, and 16 samples. More samples mean better quality, but are slower. There are two downsides: it's incompatible with N64-style depth compare and may cause minor glitches in some games.\nRecommendation: [Usually 16x MSAA, or FXAA with N64-style depth compare]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_AA_INFO, "Multisample anti-aliasing is not compatible with N64-style depth compare."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_FILTERING_GROUP, "Filtering"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ANISOTROPIC, "Anisotropic filtering:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ANISOTROPIC_OFF, "Off"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_ANISOTROPIC_HIGH, "High"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_BILINEAR, "Bilinear filtering:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_BILINEAR_STANDARD, "Standard"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_BILINEAR_3POINT, "N64-style 3 point"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_BILINEAR_TOOLTIP, "Bilinear filtering: Textures will use standard PC-style bilinear filtering.\nN64-style 3 point: Textures will be filtered more like the N64. The result is less smooth but more accurate."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_GROUP, "Dithering"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_PATTERN, "Pattern (RDRAM):"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_APPLY_TO_OUTPUT, "Apply to final output"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_APPLY_TO_OUTPUT_TOOLTIP, "This setting enables game controlled ordered grid dithering. Enable it for accurate representation. Default = disabled."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_5BIT_QUANTIZATION, "Enable 5-bit quantization"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_5BIT_QUANTIZATION_TOOLTIP, "Like real hardware this setting reduces the number of colors if dithering is used. Removes undesired dithering fragments. Default = enabled."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_HIRES_NOISE, "High resolution noise"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_HIRES_NOISE_TOOLTIP, "RDRAM dithering prevents color banding in games with framebuffer effects."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_MODE_TOOLTIP, "Settings: Disabled, Bayer ordered grid dithering, Magic Square ordered grid dithering or blue noise dithering. Blue noise dithering produces unobtrusive results. Default = blue noise dithering."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_DISABLE, "disable"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_BAYER, "Bayer"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_MAGIC_SQUARE, "Magic square"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_DITHERING_BLUE_NOISE, "Blue noise"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(VIDEO_LANGUAGE, "Language:"));

    //Emulation Tab
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_USE_PER_GAME, "Use per-game settings"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_USE_PER_GAME_TOOLTIP, "When enabled, all non-default values of settings are stored individually for each game.\nWhen a game is running, settings are displayed and saved for the currently running game.\nNote: GLideN64 already contains settings for the optimal performance of most games. Be careful when altering options on 'Emulation' and 'Frame buffer' tab.\n[Recommended: Checked]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_N64_STYLE_MIP_MAPPING, "Enable N64-style mip-mapping"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_N64_STYLE_MIP_MAPPING_TOOLTIP, "The N64 uses a unique method of mip-mapping that's difficult to reproduce correctly on PCs. When checked, this option emulates N64-accurate mip-mapping. When unchecked, some games have sharper distant textures.\n[Recommended: Checked]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_HWLIGHTING, "Enable per-pixel lighting (better quality, HLE only)"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_HWLIGHTING_TOOLTIP, "In N64 games lighting is calculated per vertex. This option enables Phong shading, which provides smoother and more realistic lighting.\n\n[Recommended: Your preference]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_SHADERS_STORAGE, "Store compiled shaders for performance (recommended)"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_SHADERS_STORAGE_TOOLTIP, "Use persistent storage for compiled shader programs.\nEach game uses a set of combiners. A combiner is an equation that defines how to build output color from various color inputs. GLideN64 translates shaders, and compiles shader programs on the fly. Shaders are large and complex. If the game uses several new combiners, compiling new shaders will take time and result in stuttering. When this option is checked, these shaders are saved so they're not recompiled the next time you run the game.\n[Recommended: Checked]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_INTERNAL_RES, "Internal resolution"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_INTERNAL_RES_TOOLTIP, "This option sets the output render buffer size. By default, the render buffer is set to the Same as output resolution, but you can set it to the Original N64 resolution or a Multiple of N64 resolution."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_FACTOR0X, "Same as output resolution"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_FACTOR1X, "Original N64 resolution (most accurate)"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_FACTORXX, "Multiple of N64 resolution:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_GAMMA, "Gamma"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_GAMMA_TOOLTIP, "Gamma correction.\nSome N64 games use gamma correction. Gamma correction makes image brighter. N64 applies gamma correction in its Video Interface. \nGLideN64 emulates gamma correction as post-processing effect. That is, it works only when frame buffer emulation enabled. Gamma correction enabled automatically for games, which use it on real N64. You may force gamma correction for all games. Default level of gamma correction is 2, as on N64.\n[Recommended: use defaults]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_GAMMA_CORRECTION, "Custom gamma correction level:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_GAMMA_INFO, "Selecting this option overrides gamma correction specified by the game."));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_2D_ELEMENTS, "2D elements"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_RENDER_2D_ELEMENTS, "Render 2D elements in N64 resolution (best quality, can be slow):"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_RENDER_2D_TOOLTIP, "When checked, 2D elements are rendered at the N64s resolution before copying them to output. This usually eliminates display issues with 2D elements, but it can be slow. This option uses heuristics to detect adjacent 2D elements that doesn't work for every game.\n[Recommended: Checked, unless you have performance problems]"));    
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_RENDER_DISABLE, "Disable"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_RENDER_ENABLE_OPTIMIZED, "Enable optimized"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_RENDER_ENABLE_UNOPTIMIZED, "Enable unoptimized"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_HALOS_REMOVAL, "Try to remove colored halos around transparent objects"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_FIX_BLACK_LINES, "Fix black lines between 2D elements:"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_FIX_BLACK_LINES_TOOLTIP, "In some games the coordinates for parts of 2D elements are not aligned: there is a half-pixel split between adjacent elements. When rendering at the N64's original resolution it isn't visible, but when the image is scaled up it results in black lines. This option attempts to connect these 2D elements.\nFor adjacent 2D elements: Apply the correction only for polygons that need it. Select this option for games that have issues with black lines.\nAlways: Apply the correction for every 2D element. Select this option when For adjacent 2D elements doesn't help.\nNever: Don't attempt to correct black lines between 2D elements.\n[Recommended: Game dependent, mostly Never]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_ADJACENT_2D_ELEMENTS, "For adjacent 2D elements"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_ALWAYS, "Always"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_NEVER, "Never"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_BACKGROUND, "Background rendering mode (HLE only):"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_BACKGROUND_TOOLTIP, "Background is a complex macro command used to render large (normally full screen) images. Since background images usually don't fit texture memory, the microcode splits them on narrow strips and renders them one by one. HLE code has two modes to emulate background commands:\nOne piece: The whole background image rendred as one textured rectangle. This method is normally much faster, but the result is not always correct.\nStripped: This method emulates background commands as close as possible to actual microcode implementation. It's slower but more precise. Another problem: some games may have gaps between rendered strips in high resolution. Use &quot;Render 2D elements in N64 resolution&quot; option to remove the gaps.\n[Recommended: Game dependent, mostly Stripped]"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_ONE_PIECE, "One piece"));
    g_defaultStrings.insert(LANG_STRINGS::value_type(EMULATION_STRIPPED, "Stripped"));
}

LANG_STR GetNextLangString(FILE * file)
{
    if (feof(file))
        return LANG_STR(0, "");

    char token = 0;
    while (token != '#' && !feof(file))
        fread(&token, 1, 1, file);

    if (feof(file))
        return LANG_STR(0, "");

    int32_t StringID;
    fscanf_s(file, "%d", &StringID);

    token = 0;
    while (token != '#' && !feof(file))
        fread(&token, 1, 1, file);

    if (feof(file))
        return LANG_STR(0, "");

    while (token != '"' && !feof(file))
        fread(&token, 1, 1, file);

    if (feof(file))
        return LANG_STR(0, "");

    fread(&token, 1, 1, file);
    std::string text;
    while (token != '"' && !feof(file)) {
        text += token;
        fread(&token, 1, 1, file);
    }

    std::string::size_type pos = text.find("\\n");
    while (pos != std::string::npos) {
        text.replace(pos, 1, "\n");
        pos = text.find("\\n", pos + 1);
    }
    return LANG_STR(StringID, text);
}

bool LoadLanguageFile(const std::string & langFile)
{
    if (g_defaultStrings.size() == 0)
        loadDefaultStrings();

    g_currentStrings.clear();
    if (g_debugLang)
        return true;

    FILE *file = NULL;
    if (fopen_s(&file, langFile.c_str(), "rb") != 0 || file == NULL)
        return false;

    uint8_t utf_bom[3];
    if (fread(&utf_bom, sizeof(utf_bom), 1, file) != 1 || utf_bom[0] != 0xEF || utf_bom[1] != 0xBB || utf_bom[2] != 0xBF) {
        fclose(file);
        return false;
    }

    while (!feof(file))
        g_currentStrings.insert(GetNextLangString(file));

    fclose(file);
    return true;
}

void LoadCurrentStrings(const char * path, const std::string & lang)
{
    std::string translationsFolder(path);
    std::replace(translationsFolder.begin(), translationsFolder.end(), '/', '\\');
    if (translationsFolder[translationsFolder.length() - 1] != '\\')
    {
        translationsFolder += '\\';
    }
    translationsFolder += "translations\\";
    if (lang.length() > 0)
    {
        std::string langFile = translationsFolder + lang;
        if (LoadLanguageFile(langFile))
        {
            return;
        }
    }
    std::string langFile = translationsFolder + "gliden64_en.Lang";
    LoadLanguageFile(langFile);
}


std::string getLangString(const char * FileName, languageStringID ID)
{
    FILE *file = NULL;
    if (fopen_s(&file, FileName, "rb") != 0 || file == NULL)
        return "";

    uint8_t utf_bom[3];
    if (fread(&utf_bom, sizeof(utf_bom), 1, file) != 1 ||
        utf_bom[0] != 0xEF ||
        utf_bom[1] != 0xBB ||
        utf_bom[2] != 0xBF)
    {
        fclose(file);
        return "";
    }

    while (!feof(file)) {
        LANG_STR String = GetNextLangString(file);
        if (String.first == ID) {
            fclose(file);
            return String.second;
        }
    }
    fclose(file);
    return "";
}

LanguageList GetLanguageList(const char * path)
{
    std::string pluginFolder(path);
    std::replace(pluginFolder.begin(), pluginFolder.end(), '/', '\\');
    if (pluginFolder[pluginFolder.length() - 1] != '\\')
    {
        pluginFolder += '\\';
    }
    pluginFolder += "translations\\";
    std::string nameFilters = pluginFolder + "gliden64_*.Lang";

    WIN32_FIND_DATAA FindData;
    HANDLE hFindFile = FindFirstFileA(nameFilters.c_str(), &FindData); // Find anything
    LanguageList languages;
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            std::string langFile = pluginFolder + FindData.cFileName;
            LanguageFile file; 

            file.Filename = FindData.cFileName;
            file.LanguageName = getLangString(langFile.c_str(), LANGUAGE_NAME);

            if (file.LanguageName.length() == 0)
                continue;

            languages.push_back(file);
        } while (FindNextFileA(hFindFile, &FindData));
        FindClose(hFindFile);
    }
    return languages;
}

const std::string & getString(languageStringID stringID)
{
    LANG_STRINGS::iterator currentString = g_currentStrings.find(stringID);
    if (currentString != g_currentStrings.end())
        return currentString->second;

    if (g_debugLang) {
        char debugStr[300];
        sprintf_s(debugStr, "#%d#", stringID);
        std::pair<LANG_STRINGS::iterator, bool> ret = g_currentStrings.insert(LANG_STRINGS::value_type(stringID, debugStr));
        if (ret.second)
            return ret.first->second;
    }

    LANG_STRINGS::iterator DefString = g_defaultStrings.find(stringID);
    if (DefString != g_defaultStrings.end())
    {
        return DefString->second;
    }
    static std::string emptyString;
    return emptyString;
}

std::wstring wGS(languageStringID StringID)
{
    return ToUTF16(getString(StringID).c_str());
}