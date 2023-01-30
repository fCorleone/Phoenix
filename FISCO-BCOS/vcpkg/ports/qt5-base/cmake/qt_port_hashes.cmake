# Every update requires an update of these hashes and the version within the control file of each of the 32 ports.
# So it is probably better to have a central location for these hashes and let the ports update via a script
set(QT_MAJOR_MINOR_VER 5.15)
set(QT_PATCH_VER 5)
set(QT_UPDATE_VERSION 0) # Switch to update qt and not build qt. Creates a file cmake/qt_new_hashes.cmake in qt5-base with the new hashes.

set(QT_PORT_LIST base 3d activeqt charts connectivity datavis3d declarative gamepad graphicaleffects imageformats location macextras mqtt multimedia networkauth
                 purchasing quickcontrols quickcontrols2 remoteobjects script scxml sensors serialport speech svg tools virtualkeyboard webchannel websockets
                 webview winextras xmlpatterns doc x11extras androidextras translations serialbus webengine webglplugin wayland)

set(QT_HASH_qt5-base             ce80eedc88abbd5a200bacc10a8e94adc1ef2122ac220715ba084adf1e32d67f2dc66168503de5fb5b5a6ab15f7a75ca23dc9956aed12ead994a8ffa6291ef87)
set(QT_HASH_qt5-3d               92c1af2ff6c3d5c8f570f93c06ae58ec14ab8c8bcbf08fdd8ef8babc497d0883c2322b163035aaa743b7e27774d9b1e97a1d4271f6b8fbea0a480985aae13fd6)
set(QT_HASH_qt5-activeqt         d439cd59714671b927aea7e2fac2f041d76f7011793f43d53ef1e098fc1e0ab5e5b92f665a4be3d03a0d7132e92fcfb2d2144029ffa123c86ea62bc30dcbe051)
set(QT_HASH_qt5-androidextras    ef9677527036359e97b3be6cc6afea088ad0dd67969f2b00dcd8799428acf2c8ab2d7db1706af8281b717ff26029943d62335e7974abef72d48af7ec0e749d07)
set(QT_HASH_qt5-charts           4ee495e932b288b18d0375b754036ecfda2447284d8a0c08b06be4588c4d5802856b2ee2ac3582427ffd08a7f4ba47626ede6524b6289acc0bbe66df0fe14ec7)
set(QT_HASH_qt5-connectivity     21fa34f6ba500b214e526aeb34308df6be6a42ac11f898f91874e1a32ae5be6f23430257a8af77e3e8b4210f17f4fdf48616500c6c9e77bb3587ceb0eb938d2b)
set(QT_HASH_qt5-datavis3d        dbea0c7197765b5eb082bd0d4f911d1465961ff2eba73f304c9934649e68e9a5c6c4948a305b94d5dea586490a633e335c47ef6b44e74ce9b1d136b700c94664)
set(QT_HASH_qt5-declarative      b4b2754ae3566bbfa3e0162738ae6ea3b36d506841ce7e4b5651d0b0ca1c341ab19f653aebc23d13a17840d391280137c463c29fcf4866fc1f1c3adf8ebb5e5b)
set(QT_HASH_qt5-doc              d5d6aa8dc5fb743276b1dcfef9c3dfb78d6a2fb25bdaa2e9a281dae6181fdc2a27a034f24e82315d144bf3f32ada54508eddfe7000c42a39d5e59df733786298)
set(QT_HASH_qt5-gamepad          504a2fc4c6b764c10af1641b8e3d3c36372ebc41efe95714c7928ae2a0b1a11c3f274e7c85ad4b7b0afeb7e309e5f1237913993a7c30345fa305f6f7ea320f3b)
set(QT_HASH_qt5-graphicaleffects 322caf42ba1be86d8872f9c86184a2b8a3bfe566c1de2492f3e22b73435fb18e0618b48f738a8edf4a1ea0ea5f6bd99862a8611c0fea97f54849bcfcbc570af7)
set(QT_HASH_qt5-imageformats     50a68bbe83fac710f21f05f3c0637beff17de00f9309aab2ceb27cfe7a178a1a56b0906f357584eef3188d7b89504591c924a9d4988a7321fb18a72271bb2dfd)
set(QT_HASH_qt5-location         5090f68926a7bc2f25ea5ae259cb87653b83fcf337c3255a7a2700724f6ac83ec2e1d9b6f38f185ab7dab84e5e042b72c58f4e4cacada6fb7d729378b93d9b3e)
set(QT_HASH_qt5-macextras        d5147706a1d1bfba6ce7489d786954dc666b94dc0172f6696e4933560ffffc91857526bf190bb60f54b0f8b2308722ed5fd1393411a55966ce855cb104bb9ff1)
set(QT_HASH_qt5-mqtt             2cc0ae1ba5f7563d2344ee4dc20843374f6f37b2fb0570d9b267ea535bcc5e6ca6ff62b5fc1ea84849fed67d8685e641100935b0dc2e2013d22396b3dabc2b82)
set(QT_HASH_qt5-multimedia       f798ffe0a32bc9f16f584b7a322c321dc2ef62c18395987ffce1f7f6cac10722c6f1166c64a1fda9877f3970a8e7b3ef8b7d9763af4c59ff313adc6081a7acfb)
set(QT_HASH_qt5-networkauth      b506fc2d44af9947e4150a4a8b1797ac41889341e60d78fbb8ebd3f27d7846e6fd8e10b694df54f04b01f16aa5af36cf1ef8e0bb30f32881074fb72beb471a1d)
set(QT_HASH_qt5-purchasing       b96177b68dc2a0e10613174ada4d14e9698692cbbe72468071f50dd86696656eae7e62ccb1ec8a32682c83a47800403f90084fed89f176733a2eaa338b9eaf50)
set(QT_HASH_qt5-quickcontrols    e7d7daeb40da76b217f6460f38532b9913e766b99b42551fde82f3a9028cd5ebfcc4874a2f2b3df086e2d17907511993f49d690203d50fa8e0c9fe076d8f47ff)
set(QT_HASH_qt5-quickcontrols2   febc0dee2408e5843a670420ac368c0a01af3ea1234c7dc6d99e3d2bb447dbe063b59e0c3b943f5a6a0705d207c21d9909787f4b80acab8bef9253714ce82a5a)
set(QT_HASH_qt5-remoteobjects    a054e22d532971752e35e127a97d51c285a21a03372b1e28f1684bb0c11afc511d461c6d4ae8f26295b4f53f16ff3d8f6e03b48031a72a6b6d2ffd27908051ef)
set(QT_HASH_qt5-script           62b1ca8684fb23357952d775f70675b2acda01d32d1672c1bdf362482632a772f1896764668c42fbc93597d6ea34afa602479d6b88e2d061f4554ab82fcd86cd)
set(QT_HASH_qt5-scxml            7c24ba2c679f74e1ef06e2c49989665d58943376dea6ddf0c92c97e7a12f57af23d2c2df98d893d2f2754658a233e3091fa669e463ee421c0aafe01fee622ca4)
set(QT_HASH_qt5-sensors          a52439dc7008dc4ee7d9af98338ed42951190d44eddca1154080f2dbfb4547fe30519b7f87f16ede2db34e0b9da2751ccd605eb9cd1bee06ab19b6122d86d620)
set(QT_HASH_qt5-serialbus        58f0e63d2af70d39190323abc29f218e657eb892eacf4886a7eb9b7558f9c06288a51c85ebeb2982af58c8909f1de865b5089907cfffa1ff2938723b66b0d7a8)
set(QT_HASH_qt5-serialport       479bc5a4bddc4cb7659d2768b51947847f3c413102554fe3883e1decc42e6c9d0ad693627f607bd8cec43fd014e495fa9812934dd1b8ce1cf3f3ad46b5f6c774)
set(QT_HASH_qt5-speech           b2f3a83a462c1f067804f8c2c28e47e76588cc5d70e3f0ec66a1955890b6a419371a769ec6f8867947f4a81cfc91db3bc65c1d628038cdec6c722cbfc1217aba)
set(QT_HASH_qt5-svg              7938a84abca282f263f7840425863379ed9e0f9854ecfe38e5d1edacdaf39b2516e9e9b8b5dbcf52113785d8c4123ebea550f441abc000d01c07a20a6a742ac4)
set(QT_HASH_qt5-tools            ff5e658ec812dd36d00ad3ac7e824de708968ff1c66a73da1470b6f0cdb6853a7084f18b1bcf1614afd4c23f381d817d7eb665f8573a4e981a9b87c6e4d6fa2b)
set(QT_HASH_qt5-translations     56a13156f7a7cde347b6413eb1f1f29121a70a8e20fd1d947fe093d6721598da26f63fc49aa6f99a4f4c1d213ea426d8e6897b51d858881a2d31d121740a60d3)
set(QT_HASH_qt5-virtualkeyboard  d6ef4a067fc0af3bf562f68382b32c2eccaf21638cd89a79ad011fd640581448e997d67f5994ef1ac975df501cf6a57321d6f37426901f3db70c28c14925737b)
set(QT_HASH_qt5-wayland          828dceb7bc54ce610a73f110f0aca332a90cf95df4a3bc971bd21c4e878366cb8d2248e609b73ce4d381579a143843c87a62f23dcc95767e522874e53a1b0327)
set(QT_HASH_qt5-webchannel       74ac09f418fd918cf5930f7d985fd69477da3ef1ecdedcf4b59eb9c17b43849876141ed6483dc32ef3e5e3f3fbc2a6babeb281f72da7850bfc677f2acfaad3fe)
set(QT_HASH_qt5-webengine        9dc7891c452397878fb20bd64ec00b13a056e9eff33f74ac3a9c06bc93992ae2ce49b8f8cef553d3f681c37d81a81ee5af29d317ca1963b4793d32841aa316f0)
set(QT_HASH_qt5-webglplugin      c9e5451ced0e3cf12612edf7744d1a916d83307ded70fe61cbbf21f13966d3e42d0647f76a6d848f75dd0477efdfb87367634be3af8f187aec310d88f4b0acf5)
set(QT_HASH_qt5-websockets       2d44983e462a899c4adb90998b84d24466d70d8fab340481bc916228b289c45456ea5acde61a70aa9e3f9233216c5ca80375f190d9cbc406f8d40b535e90e480)
set(QT_HASH_qt5-webview          ad6a9839c1a6e5b037b687bc1cec75a3cf8d10d66861ce88137c32107fca7351e8801da2a7ff623b0aaa1ced7430c4733593b5ec2d2bfdb7de98d9aeb9411287)
set(QT_HASH_qt5-winextras        2986aa9403fd3d5a5415d93fe607bc0e36fd90fa56c01af817054aaca9e7614259343a7c16db75a2f5a96c05e1a38b3e068fc4e45de967ebcd3ed136bc6a886a)
set(QT_HASH_qt5-x11extras        19ca14f0d4bcee08077cbbe81a8e6537fcc134036da1217c9744411d53ca5ebc14e96a8c25b15eb81795697628e6f64611dd3bc822621adcd4420a58a0c335b1)
set(QT_HASH_qt5-xmlpatterns      553456f299c6812c058496f5e1d6a089df1f693dd1105fed80e6d6dd0cf143a0d74ade44408f48553ff3fac0951ab3f7384bc08535888354d921aa2d8428317d)

if(QT_UPDATE_VERSION)
    message(STATUS "Running Qt in automatic version port update mode!")
    set(_VCPKG_INTERNAL_NO_HASH_CHECK 1)
    if("${PORT}" MATCHES "qt5-base")
        function(update_qt_version_in_manifest _port_name)
            set(_current_control "${VCPKG_ROOT_DIR}/ports/${_port_name}/vcpkg.json")
            file(READ ${_current_control} _control_contents)
            #message(STATUS "Before: \n${_control_contents}")
            string(REGEX REPLACE "\"version.*\": \"[0-9]+\.[0-9]+\.[0-9]+\",\n" "\"version\": \"${QT_MAJOR_MINOR_VER}.${QT_PATCH_VER}\",\n" _control_contents "${_control_contents}")
            string(REGEX REPLACE "\n  \"port-version\": [0-9]+," "" _control_contents "${_control_contents}")
            #message(STATUS "After: \n${_control_contents}")
            file(WRITE ${_current_control} "${_control_contents}")
            configure_file("${_current_control}" "${_current_control}" @ONLY NEWLINE_STYLE LF)
        endfunction()

        update_qt_version_in_manifest("qt5")
        foreach(_current_qt_port_basename ${QT_PORT_LIST})
            update_qt_version_in_manifest("qt5-${_current_qt_port_basename}")
        endforeach()
    endif()
endif()