// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.33.0
// 	protoc        v3.19.4
// source: auth/auth.proto

package auth

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type AuthRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields
}

func (x *AuthRequest) Reset() {
	*x = AuthRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_auth_auth_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *AuthRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*AuthRequest) ProtoMessage() {}

func (x *AuthRequest) ProtoReflect() protoreflect.Message {
	mi := &file_auth_auth_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use AuthRequest.ProtoReflect.Descriptor instead.
func (*AuthRequest) Descriptor() ([]byte, []int) {
	return file_auth_auth_proto_rawDescGZIP(), []int{0}
}

type AuthResponse struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Appid              string `protobuf:"bytes,1,opt,name=appid,proto3" json:"appid,omitempty"`
	Secret             string `protobuf:"bytes,2,opt,name=secret,proto3" json:"secret,omitempty"`
	OssEndpoint        string `protobuf:"bytes,3,opt,name=oss_endpoint,json=ossEndpoint,proto3" json:"oss_endpoint,omitempty"`
	OssAccessKeyId     string `protobuf:"bytes,4,opt,name=oss_access_key_id,json=ossAccessKeyId,proto3" json:"oss_access_key_id,omitempty"`
	OssAccessKeySecret string `protobuf:"bytes,5,opt,name=oss_access_key_secret,json=ossAccessKeySecret,proto3" json:"oss_access_key_secret,omitempty"`
}

func (x *AuthResponse) Reset() {
	*x = AuthResponse{}
	if protoimpl.UnsafeEnabled {
		mi := &file_auth_auth_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *AuthResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*AuthResponse) ProtoMessage() {}

func (x *AuthResponse) ProtoReflect() protoreflect.Message {
	mi := &file_auth_auth_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use AuthResponse.ProtoReflect.Descriptor instead.
func (*AuthResponse) Descriptor() ([]byte, []int) {
	return file_auth_auth_proto_rawDescGZIP(), []int{1}
}

func (x *AuthResponse) GetAppid() string {
	if x != nil {
		return x.Appid
	}
	return ""
}

func (x *AuthResponse) GetSecret() string {
	if x != nil {
		return x.Secret
	}
	return ""
}

func (x *AuthResponse) GetOssEndpoint() string {
	if x != nil {
		return x.OssEndpoint
	}
	return ""
}

func (x *AuthResponse) GetOssAccessKeyId() string {
	if x != nil {
		return x.OssAccessKeyId
	}
	return ""
}

func (x *AuthResponse) GetOssAccessKeySecret() string {
	if x != nil {
		return x.OssAccessKeySecret
	}
	return ""
}

var File_auth_auth_proto protoreflect.FileDescriptor

var file_auth_auth_proto_rawDesc = []byte{
	0x0a, 0x0f, 0x61, 0x75, 0x74, 0x68, 0x2f, 0x61, 0x75, 0x74, 0x68, 0x2e, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x12, 0x04, 0x61, 0x75, 0x74, 0x68, 0x22, 0x0d, 0x0a, 0x0b, 0x41, 0x75, 0x74, 0x68, 0x52,
	0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x22, 0xbd, 0x01, 0x0a, 0x0c, 0x41, 0x75, 0x74, 0x68, 0x52,
	0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x12, 0x14, 0x0a, 0x05, 0x61, 0x70, 0x70, 0x69, 0x64,
	0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x05, 0x61, 0x70, 0x70, 0x69, 0x64, 0x12, 0x16, 0x0a,
	0x06, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x06, 0x73,
	0x65, 0x63, 0x72, 0x65, 0x74, 0x12, 0x21, 0x0a, 0x0c, 0x6f, 0x73, 0x73, 0x5f, 0x65, 0x6e, 0x64,
	0x70, 0x6f, 0x69, 0x6e, 0x74, 0x18, 0x03, 0x20, 0x01, 0x28, 0x09, 0x52, 0x0b, 0x6f, 0x73, 0x73,
	0x45, 0x6e, 0x64, 0x70, 0x6f, 0x69, 0x6e, 0x74, 0x12, 0x29, 0x0a, 0x11, 0x6f, 0x73, 0x73, 0x5f,
	0x61, 0x63, 0x63, 0x65, 0x73, 0x73, 0x5f, 0x6b, 0x65, 0x79, 0x5f, 0x69, 0x64, 0x18, 0x04, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x0e, 0x6f, 0x73, 0x73, 0x41, 0x63, 0x63, 0x65, 0x73, 0x73, 0x4b, 0x65,
	0x79, 0x49, 0x64, 0x12, 0x31, 0x0a, 0x15, 0x6f, 0x73, 0x73, 0x5f, 0x61, 0x63, 0x63, 0x65, 0x73,
	0x73, 0x5f, 0x6b, 0x65, 0x79, 0x5f, 0x73, 0x65, 0x63, 0x72, 0x65, 0x74, 0x18, 0x05, 0x20, 0x01,
	0x28, 0x09, 0x52, 0x12, 0x6f, 0x73, 0x73, 0x41, 0x63, 0x63, 0x65, 0x73, 0x73, 0x4b, 0x65, 0x79,
	0x53, 0x65, 0x63, 0x72, 0x65, 0x74, 0x32, 0x8c, 0x01, 0x0a, 0x0b, 0x41, 0x75, 0x74, 0x68, 0x53,
	0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0x43, 0x0a, 0x18, 0x67, 0x65, 0x74, 0x5f, 0x77, 0x78,
	0x5f, 0x6d, 0x69, 0x6e, 0x69, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x5f, 0x74, 0x6f, 0x6b,
	0x65, 0x6e, 0x12, 0x11, 0x2e, 0x61, 0x75, 0x74, 0x68, 0x2e, 0x41, 0x75, 0x74, 0x68, 0x52, 0x65,
	0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x12, 0x2e, 0x61, 0x75, 0x74, 0x68, 0x2e, 0x41, 0x75, 0x74,
	0x68, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x22, 0x00, 0x12, 0x38, 0x0a, 0x0d, 0x67,
	0x65, 0x74, 0x5f, 0x6f, 0x73, 0x73, 0x5f, 0x74, 0x6f, 0x6b, 0x65, 0x6e, 0x12, 0x11, 0x2e, 0x61,
	0x75, 0x74, 0x68, 0x2e, 0x41, 0x75, 0x74, 0x68, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a,
	0x12, 0x2e, 0x61, 0x75, 0x74, 0x68, 0x2e, 0x41, 0x75, 0x74, 0x68, 0x52, 0x65, 0x73, 0x70, 0x6f,
	0x6e, 0x73, 0x65, 0x22, 0x00, 0x42, 0x2e, 0x5a, 0x2c, 0x67, 0x69, 0x74, 0x68, 0x75, 0x62, 0x2e,
	0x63, 0x6f, 0x6d, 0x2f, 0x70, 0x6b, 0x75, 0x73, 0x75, 0x6e, 0x6a, 0x79, 0x2f, 0x6f, 0x70, 0x65,
	0x6e, 0x61, 0x69, 0x2d, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x2d, 0x70, 0x72, 0x6f, 0x74, 0x6f,
	0x2f, 0x61, 0x75, 0x74, 0x68, 0x62, 0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_auth_auth_proto_rawDescOnce sync.Once
	file_auth_auth_proto_rawDescData = file_auth_auth_proto_rawDesc
)

func file_auth_auth_proto_rawDescGZIP() []byte {
	file_auth_auth_proto_rawDescOnce.Do(func() {
		file_auth_auth_proto_rawDescData = protoimpl.X.CompressGZIP(file_auth_auth_proto_rawDescData)
	})
	return file_auth_auth_proto_rawDescData
}

var file_auth_auth_proto_msgTypes = make([]protoimpl.MessageInfo, 2)
var file_auth_auth_proto_goTypes = []interface{}{
	(*AuthRequest)(nil),  // 0: auth.AuthRequest
	(*AuthResponse)(nil), // 1: auth.AuthResponse
}
var file_auth_auth_proto_depIdxs = []int32{
	0, // 0: auth.AuthService.get_wx_miniprogram_token:input_type -> auth.AuthRequest
	0, // 1: auth.AuthService.get_oss_token:input_type -> auth.AuthRequest
	1, // 2: auth.AuthService.get_wx_miniprogram_token:output_type -> auth.AuthResponse
	1, // 3: auth.AuthService.get_oss_token:output_type -> auth.AuthResponse
	2, // [2:4] is the sub-list for method output_type
	0, // [0:2] is the sub-list for method input_type
	0, // [0:0] is the sub-list for extension type_name
	0, // [0:0] is the sub-list for extension extendee
	0, // [0:0] is the sub-list for field type_name
}

func init() { file_auth_auth_proto_init() }
func file_auth_auth_proto_init() {
	if File_auth_auth_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_auth_auth_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*AuthRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_auth_auth_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*AuthResponse); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_auth_auth_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   2,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_auth_auth_proto_goTypes,
		DependencyIndexes: file_auth_auth_proto_depIdxs,
		MessageInfos:      file_auth_auth_proto_msgTypes,
	}.Build()
	File_auth_auth_proto = out.File
	file_auth_auth_proto_rawDesc = nil
	file_auth_auth_proto_goTypes = nil
	file_auth_auth_proto_depIdxs = nil
}
