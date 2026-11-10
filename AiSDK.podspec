#
# Be sure to run `pod lib lint AiSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'AiSDK'
  s.version          = '1.3.4'
  s.swift_version    = '5.0'
  s.summary          = 'Huawo AiSDK.'
  s.description      = <<-DESC
None
                       DESC

  s.homepage         = 'https://github.com/HWdan/HwAiSDK.git'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'sujiang' => 'sujiang@huawo-wear.com' }
  s.source           = { :git => 'https://github.com/HWdan/HwAiSDK.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '12.0'

  s.source_files = 'AiSDK/Classes/**/*'
  s.private_header_files = 'AiSDK/Classes/Handler/AiSDK+BmpConverterInternal.h'
  
  s.resource_bundles = {
    'AiSDK' => ['AiSDK/Assets/*.png']
  }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
 s.dependency 'AFNetworking', '~> 4.0.1'
# s.dependency 'HwBluetoothSDK'
 s.dependency 'WatchfaceSDK'
 s.dependency 'SSZipArchive'
 s.vendored_frameworks = 'HwBluetoothSDK.framework','NativeLib.xcframework'
 # Both vendored binaries are static archives. Keep AiSDK dynamic (do not set
 # static_framework) so CocoaPods links them into this one framework. A static
 # AiSDK copies HwBluetoothDevice and the other classes into every target that
 # depends on it, and Swift crashes when it bridges the scan-device array.
 # -ObjC keeps categories from the static archives. NativeLib needs the LLVM
 # profiling runtime in the image that actually links it.
 s.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '$(inherited) -ObjC -fprofile-instr-generate' }
end
