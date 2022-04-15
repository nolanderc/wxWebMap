//#include	<wxMapMarker.h>
#include	<wxMapImageS.h>
#include    <wx/tokenzr.h>
#include    <wx/log.h>
#include    <wx/intl.h>

wxString wxMapObject::GetRemoveString(wxString const& map)
{
    return wxString::Format("mapobject_remove(%d, %s); \n", cLeafletId, map);
}

bool wxMapObject::ParseResult(wxString const& result, EMapObjectType& type, int& id)
{
    wxStringTokenizer parse(result, ",");
    int i = 0;
    bool bOk = true;
    while (parse.HasMoreTokens()) {
        wxString token = parse.GetNextToken();
        switch (i) {
        case 0:
            // Parse type:
            if (token.IsSameAs("IMAGE")) {
                type = EMapObjectType::IMAGE;
            }
            break;
        case 1:

        {
            // Parse id
            long lid;
            if (!token.ToLong(&lid)) {
                wxLogError(_("Could not parse result as id: %s"), token);
                bOk = false;
            }
            id = (int)lid;
        }
        break;
        }
        ++i;
    }
    return bOk;
}

wxMapImageS::wxMapImageS(double lat, double lon, bool bDraggable) :
    cLat(lat),
    cLon(lon),
    cbDraggable(bDraggable)
{
    cType = EMapObjectType::IMAGE;
}

wxString wxMapImageS::GetJavaScriptAdd(wxString map) const
{
    if (!cbDraggable) {
        return wxString::Format("image_add(%.6lf,%.6lf,%s); \n", cLat, cLon, map);
    }
    else {
        return wxString::Format("marker_add_drag(%.6lf,%.6lf,%s); \n", cLat, cLon, map);
    }
    return wxEmptyString;
}

pwxMapImageS wxMapImageS::Create(double lat, double lon, bool bDraggable)
{
    return boost::make_shared<wxMapImageS>(lat, lon, bDraggable);
}