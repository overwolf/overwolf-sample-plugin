Overwolf sample plugin
======================

If you want to leverage your existing C/C++ code you can wrap it inside an NPAPI (Netscape Plugin API) DLL file and communicate with it via your Overwolf WebApp.

npOverwolfSamplePlugin
======================
This is a Skeleton NPAPI project that compiles (VS2010) to a DLL that you can later reference in your app.  In order to make it compile, you'll need to download the xulrunner-sdk.

You can get xulrunner-sdk from: https://developer.mozilla.org/en/docs/Gecko_SDK.

NOTE: Was successfully tested with version Gecko 1.9.2 (Firefox 3.6).

Unzip the xulrunner-sdk folder side-by-side with the npOverwolfSamplePlugin folder - the project references this folder (see Additional Include Directories).

NOTE: we make sure to compile the plugin /MT so there are no dependencies on the C runtime libraries.



The sample plugin exposes the following methods for your WebApp:

- echo("string", function(data) {...});
- add(1, 2, function(sum) {...});

As well as a single read-only property:

- sampleProperty which returns the value 42 (a hardcoded value). 


Sample Overwolf WebApp
======================
This is an unpacked Overwolf WebApp that utilizes the Overwolf sample plugin.

NOTE: the npOverwolfSamplePlugin.dll file is placed inside of the WebApp's directory - so if you recompile it, you'll need to place the new DLL file inside the folder (overriding the existing dll file).

Please review the manifest.json file to view how to reference the NPAPI file.

Please, don't hesitate to ask us questions in our developers forum: http://forums.overwolf.com/.

The Overwolf Team