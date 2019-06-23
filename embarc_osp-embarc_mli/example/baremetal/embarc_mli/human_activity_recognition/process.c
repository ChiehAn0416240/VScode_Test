/* ------------------------------------------
 * Copyright (c) 2019, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

#include "embARC.h"
#include "embARC_debug.h"
#include "process.h"
#include "memory.h"
#include "input_buffer.h"
#include "settings.h"

#include "har_smartphone_model.h"

static d_type const_1;

#define FLOAT_TO_DTYPE(val) (d_type)((val) * const_1)
#define DTYPE_TO_FLOAT(val) ((float)(val) / const_1)

/*
 * Input data pre-processing 
 */

void preprocess_init(void)
{
    const_1 = (1 << har_smartphone_net_input->el_params.fx.frac_bits) - 1;
}
 
void preprocess_tensor_data(float *in)
{
    d_type *out = (d_type *)har_smartphone_net_input->data;
    uint32_t col, row;

    /* Convert floating point values to the tensor data type 
       (see d_type definition for the particular platform) */
    for(row=0; row<har_smartphone_net_input->shape[0]; row++) {
        for(col=0; col<har_smartphone_net_input->shape[1]; col++) {
            *out++ = FLOAT_TO_DTYPE(*in++);
        }
    }
}

/*
 * Result post-processing 
 */

void postprocess_tensor_data()
{
    d_type *result= (d_type *)har_smartphone_net_output->data;
    float coeff[6];
    uint32_t index;

    for(index=0; index<6; index++) {
        coeff[index] = DTYPE_TO_FLOAT(result[index]);
    }
}
