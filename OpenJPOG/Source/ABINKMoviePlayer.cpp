#include "ABINKMoviePlayer.h"

TOSHI_NAMESPACE_USING

static U32 s_iPlayForegroundFast = 0;

ABINKMoviePlayer::ABINKMoviePlayer()
{
    m_bHasMovieStopped = TTRUE;
    m_bIsBINKInitialized = TFALSE;
    m_hBink = NULL;
    m_iFrameBufferHeight = 0;
    m_iFrameBufferWidth = 0;
    m_pFrameBufferBits = TNULL;
    RADSetMemory(RADMEMALLOC, RADMEMFREE);
    SetFrameReady(TFALSE);
}

TBOOL ABINKMoviePlayer::InitializeMoviePlayer()
{
    HRESULT hResult = DirectSoundCreate(NULL, &m_pDirectSound, NULL);
    if (FAILED(hResult)) {
        m_pDirectSound = NULL;
    }
    else {
        BinkSoundUseDirectSound(m_pDirectSound);
    }
    return TTRUE;
}

TBOOL ABINKMoviePlayer::ShutdownMoviePlayer()
{
    if (m_bIsBINKInitialized) {
        FreeAudioResource();
        FreeVideoResource();
        m_bIsBINKInitialized = TFALSE;
        SetFrameReady(TFALSE);
    }
    return TFALSE;
}

TBOOL ABINKMoviePlayer::Update(TFLOAT a_fDeltaTime)
{
    if (!m_bHasMovieStopped && m_hBink) {
        BinkService(m_hBink);
        if (BinkWait(m_hBink)) {
            BinkSleep(500);
            return TFALSE;
        }
        RenderToFrameBuffer();
    }
    return TFALSE;
}

TBOOL ABINKMoviePlayer::RenderToTexture(TTextureResource* a_pTexture)
{
    if (m_hBink) {
        m_iWidth = m_hBink->Width;
        m_iHeight = m_hBink->Height;
        if (a_pTexture && !m_bHasMovieStopped) {
            if (s_iPlayForegroundFast) {
                BinkDoFrame(m_hBink);
                BinkNextFrame(m_hBink);
                return FALSE;
            }
            m_iFrameCount++;
            // TODO: Do some Texture stuff
            BinkDoFrame(m_hBink);
            if (m_iFrameCount == m_hBink->Frames) {

            }
        }
    }
    return TBOOL();
}

TBOOL ABINKMoviePlayer::RenderToFrameBuffer()
{
    if (!m_bHasMovieStopped && !m_bRenderingTiles) {
        RenderToTiles();
        m_bRenderingTiles = TTRUE;
    }
    return TFALSE;
}

TBOOL ABINKMoviePlayer::RenderToFrameBuffer(TPBYTE a_pDest, TINT a_iDestWidth, TINT a_iDestHeigth, TINT a_iDestPitch, TINT a_iDestX, INT a_iDestY, INT a_iSrcX, INT a_iSrcY)
{
    BinkCopyToBufferRect(m_hBink, a_pDest, a_iDestPitch, a_iDestHeigth,
        a_iDestX, a_iDestY, a_iSrcX, a_iSrcY, m_hBink->Width, m_hBink->Height, BINKCOPYALL | BINKNOSKIP | BINKSURFACE32A);
    TPBYTE pBuf = a_pDest + a_iDestX + a_iDestY * a_iDestWidth;

    if (a_iDestHeigth == a_iDestWidth) {
        // I think this ignores alpha?
        for (TINT i = 0; i < a_iDestHeigth; i++) {
            for (TINT j = 0; j < a_iDestWidth; j++) {
                *pBuf = *pBuf | 0xFF000000;
            }
            pBuf += a_iDestPitch * 4;
        }
    }
    else if (a_iDestHeigth != a_iDestWidth && a_iDestHeigth - a_iDestWidth >= 0) {
        // I think this ignores alpha?
        for (TINT i = 0; i < a_iDestWidth; i++) {
            for (TINT j = 0; j < a_iDestWidth; j++) {
                *pBuf = *pBuf | 0xFF000000;
            }
            pBuf += a_iDestPitch * 4;
        }
    }
    
    return TFALSE;
}

void ABINKMoviePlayer::BinkSleep(TINT a_iMicroseconds)
{
    static S32 s_iTotalSleep = 0;
    static S32 s_iSleepForward = 0;
    static U64 s_iFrequency = 1000;
    static S32 s_bFrequencyAquired = 0;

    if (!s_bFrequencyAquired)
    {
        s_bFrequencyAquired = 1;
        QueryPerformanceFrequency((LARGE_INTEGER*)&s_iFrequency);
    }

    s_iTotalSleep += a_iMicroseconds;

    if ((s_iTotalSleep - s_iSleepForward) > 1000)
    {
        U64 start, end;
        s_iTotalSleep -= s_iSleepForward;

        QueryPerformanceCounter((LARGE_INTEGER*)&start);
        Sleep(s_iTotalSleep / 1000);
        QueryPerformanceCounter((LARGE_INTEGER*)&end);

        end = ((end - start) * (U64)1000000) / s_iFrequency;

        s_iSleepForward = (U32)end - s_iTotalSleep;
        s_iTotalSleep %= 1000;
    }
}

TBOOL ABINKMoviePlayer::RenderToTiles()
{
    return TBOOL();
}