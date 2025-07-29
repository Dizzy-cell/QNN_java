import torch

import qai_hub as hub
from qai_hub_models.models.esrgan import Model

# Load the model
# torch_model = Model.from_pretrained()

# Device
device = hub.Device("Samsung Galaxy S24")

# # Trace model
# input_shape = torch_model.get_input_spec()
# sample_inputs = torch_model.sample_inputs()
#
# pt_model = torch.jit.trace(torch_model, [torch.tensor(data[0]) for _, data in sample_inputs.items()])

model_tf = 'ESRGAN.tflite'
model_onnx = 'ESRGAN.onnx'
model_bin ='esrgan.bin'

model_onnx = 'XLSR.onnx'
model_bin = 'xlsr.bin'
model_bin ='libxlsr.so'

input_shape = (1, 3, 128, 128)

# Compile model on a specific device
compile_job = hub.submit_compile_job(
    model=model_onnx,
    device=device,
    input_specs=dict(image=input_shape),
    #options="--target_runtime qnn_context_binary --force_channel_last_input image --force_channel_last_output output_0",
    options="--target_runtime qnn_lib_aarch64_android --force_channel_last_input image --force_channel_last_output output_0"
)

# Get target model to run on-device
# compile_job = hub.get_job("")
target_model = compile_job.get_target_model()
#target_model = hub.get_model("mnld713om")
target_model.download(model_bin)


# qai-hub configure --api_token