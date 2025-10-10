#
# Be sure to run `pod lib lint AiSDK.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see https://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'AiSDK'
  s.version          = '1.3.2'
  s.swift_version    = '5.0'
  s.summary          = 'Huawo AiSDK.'
  s.description      = <<-DESC
None
                       DESC

  s.homepage         = 'https://github.com/HWdan/HwAiSDK.git'
  # s.screenshots     = 'www.example.com/screenshots_1', 'www.example.com/screenshots_2'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'huangwentai' => 'hwt1573tiger@163.com' }
  s.source           = { :git => 'https://github.com/HWdan/HwAiSDK.git', :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

  s.ios.deployment_target = '9.0'

  s.source_files = 'AiSDK/Classes/**/*'
  
  s.resource_bundles = {
    'AiSDK' => ['AiSDK/Assets/*.png']
  }

  # s.public_header_files = 'Pod/Classes/**/*.h'
  # s.frameworks = 'UIKit', 'MapKit'
 s.dependency 'AFNetworking', '~> 4.0.1'
 s.dependency 'HwBluetoothSDK'
 s.dependency 'WatchfaceSDK'
 s.dependency 'SSZipArchive'
 s.vendored_frameworks = 'NativeLib.xcframework'
end
