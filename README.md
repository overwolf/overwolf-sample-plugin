overwolf-sample-plugin
======================

If you want to leverage your existing C/C++ code
you can wrap it inside an NPAPI (Netscape Plugin API)
DLL file and communicate with it via your Overwolf
WebApp.

This folder contains the following:

npOverwolfSamplePlugin
======================
a Skeleton NPAPI project that
compiles (VS2010) to a DLL that you can later reference
in your app.

In order to make it compile, you'll need to download the xulrunner-sdk.

Get xulrunner-sdk from: https://developer.mozilla.org/en/docs/Gecko_SDK 
NOTE: Was tested successfully with version: Gecko 1.9.2 (Firefox 3.6)
Seems like the latest version has issues with NPP_GetMIMEDescription 
returning: const char* and not char* (?)

Unzip the xulrunner-sdk folder, side-by-side, with the npOverwolfSamplePlugin
folder - the project references this folder (Additional Include Directories)

NOTE: we make sure to compile the plugin /MT so there are
no dependencies on the c runtime libraries.



The sample plugin exposes the following methods:

echo("string", function(data) {...});
add(1, 2, function(sum) {...});

and a single read-only property:

sampleProperty that returns the hardcoded value of 42


sample app
==========
An unpacked sample Overwolf WebApp that utilizes the sample
NPAPI.

NOTE: the npOverwolfSamplePlugin.dll is placed inside this
directory - so if you change and recompile it, you'll need
to place the changes inside the folder (overriding the existing
dll file)

Please review the manifest.json file to see how to reference
the NPAPI.

You can always open the Dev-Tools by giving the app's window
focus and pressing: Ctrl + Shift + i and debug it


Please, don't hesitate to post questions in our developers forum.

The Overwolf Team