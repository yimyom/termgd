#include <R.h>
#include <R_ext/GraphicsDevice.h>
#include <R_ext/GraphicsEngine.h>
#include <Rinternals.h>

static void termgd_activate(pDevDesc dd)
{
}
static void termgd_deactivate(pDevDesc dd)
{
}
static void termgd_size(double *left, double *right, double *bottom, double *top, pDevDesc dd)
{
    *left = dd->left;
    *right = dd->right;
    *bottom = dd->bottom;
    *top = dd->top;
}
static void termgd_newPage(const pGEcontext gc, pDevDesc dd)
{
}
static void termgd_close(pDevDesc dd)
{
}
static void termgd_clip(double x0, double x1, double y0, double y1, pDevDesc dd)
{
}
static double termgd_strWidth(const char *str, const pGEcontext gc, pDevDesc dd)
{
    return 0;
}
static void termgd_text(double x, double y, const char *str, double rot, double hadj, const pGEcontext gc,
                            pDevDesc dd)
{
}
static void termgd_rect(double x0, double y0, double x1, double y1, const pGEcontext gc, pDevDesc dd)
{
}
static void termgd_line(double x1, double y1, double x2, double y2, const pGEcontext gc, pDevDesc dd)
{
}
static void termgd_polyline(int n, double *x, double *y, const pGEcontext gc, pDevDesc dd)
{
}
static void termgd_polygon(int n, double *x, double *y, const pGEcontext gc, pDevDesc dd)
{
}
static void termgd_raster(unsigned int *raster, int w, int h, double x, double y, double width, double height,
                              double rot, Rboolean interpolate, const pGEcontext gc, pDevDesc dd)
{
}
static void termgd_mode(int mode, pDevDesc dd)
{
}

static RdevDesc termgd_driver = {R_DEVICE_VERSION,
                                     "termgd",
                                     NULL,
                                     NULL,
                                     NULL, // startDevice and closeDevice set later
                                     termgd_activate,
                                     termgd_deactivate,
                                     termgd_size,
                                     termgd_newPage,
                                     termgd_clip,
                                     termgd_strWidth,
                                     termgd_text,
                                     NULL,
                                     NULL,
                                     FALSE,
                                     FALSE,
                                     FALSE,
                                     NULL,
                                     termgd_line,
                                     termgd_polyline,
                                     termgd_polygon,
                                     NULL,
                                     termgd_raster,
                                     NULL,
                                     NULL,
                                     R_NilValue,
                                     NULL,
                                     NULL,
                                     termgd_mode};

static DevDesc *termgd_start(double width, double height, double pointsize)
{
    DevDesc *dd = GEcreateDevDesc(&termgd_driver);
    if (!dd)
        return NULL;

    dd->left = 0;
    dd->right = width * 72;
    dd->bottom = height * 72;
    dd->top = 0;
    dd->cra[0] = 0.9 * pointsize;
    dd->cra[1] = 1.2 * pointsize;
    dd->ipr[0] = dd->ipr[1] = 1.0 / 72.0;
    dd->canClip = TRUE;
    return dd;
}

SEXP termgd_create(SEXP width, SEXP height, SEXP pointsize)
{
    double w = REAL(width)[0], h = REAL(height)[0], ps = REAL(pointsize)[0];
    DevDesc *dd = termgd_start(w, h, ps);
    if (!dd)
        error("Device creation failed");
    GEaddDevice2(dd, "termgd");
    return R_NilValue;
}

#include <R_ext/Rdynload.h>
static const R_CallMethodDef callMethods[] = {{"termgd_create", (DL_FUNC)&termgd_create, 3}, {NULL, NULL, 0}};

void R_init_termgd(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, callMethods, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
