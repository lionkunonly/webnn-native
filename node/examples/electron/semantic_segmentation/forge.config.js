const fse = require('fs-extra');

module.exports = {
  packagerConfig: {
    asar: {
      unpack: "node_setup.js",
      unpackDir: "{lib,build}"
   },
  },
  makers: [
    {
      name: '@electron-forge/maker-zip'
    }
   ],
  hooks: {
    generateAssets: async () => {
      // Copy WebNN libs, source code and dependences of semantic segmentation sample
      const node_path = '../../../';
      const samples_path = node_path + 'third_party/webnn-samples/';
      const copy_list = [
        {"from": `${node_path}node_setup.js`, "to": 'node_setup.js'},
        {"from": `${node_path}lib`, "to": 'lib'},
        {"from": `${node_path}build`, "to": 'build'},
        {"from": `${samples_path}common`, "to": 'common'},
        {"from": `${samples_path}test-data/models/deeplabv3_mnv2_nhwc`,
         "to": 'test-data/models/deeplabv3_mnv2_nhwc'},
         {"from": `${samples_path}test-data/models/deeplabv3_mnv2_nchw`,
         "to": 'test-data/models/deeplabv3_mnv2_nchw'},
        {"from": `${samples_path}semantic_segmentation`,
         "to": 'semantic_segmentation'},
      ];
     for (let copy of copy_list) {
      await fse.copy(copy.from, copy.to, {overwrite: true});
     }

      console.log('Copy WebNN libs and samples successfully!');
    }
  }
}
